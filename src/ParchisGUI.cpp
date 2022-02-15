# include "ParchisGUI.h"

ParchisGUI::ParchisGUI(Parchis &model)
    : game_window(VideoMode(1600, 800), L"Parchís", Style::Titlebar | Style::Close)
    // L"string" parece que permite representar caraceteres unicode. Útil para acentos y demás.
{
    this->model = &model;

    this->clicked = false;

    //Cargamos las texturas
    this->tPieces.loadFromFile("data/textures/fichas_parchis_resized.png");
    this->tBoard.loadFromFile("data/textures/parchis_board_resized.png");
    this->tDices.loadFromFile("data/textures/dice1.png");

    //Definimos los sprites
    this->board = Sprite(tBoard);
    //Fichas rojas
    vector<Sprite> red_pieces_sprites;
    for (int i = 0; i < model.getBoard().getPieces(color::red).size() ; i++){
        red_pieces_sprites.push_back(Sprite(tPieces));
        red_pieces_sprites[i].setTextureRect(IntRect(30,30,30,30));
        red_pieces_sprites[i].setPosition((Vector2f) box2position[model.getBoard().getPiece(color::red, i)][i]);
    }
    pieces.insert({color::red, red_pieces_sprites});


    vector<Sprite> blue_pieces_sprites;
    for (int i = 0; i < model.getBoard().getPieces(color::blue).size() ; i++){
        blue_pieces_sprites.push_back(Sprite(tPieces));
        blue_pieces_sprites[i].setTextureRect(IntRect(0,30,30,30));
        blue_pieces_sprites[i].setPosition((Vector2f) box2position[model.getBoard().getPiece(color::blue, i)][i]);
    }
    pieces.insert({color::blue, blue_pieces_sprites});

    vector<Sprite> green_pieces_sprites;
    for (int i = 0; i < model.getBoard().getPieces(color::green).size() ; i++){
        green_pieces_sprites.push_back(Sprite(tPieces));
        green_pieces_sprites[i].setTextureRect(IntRect(30,0,30,30));
        green_pieces_sprites[i].setPosition((Vector2f) box2position[model.getBoard().getPiece(color::green, i)][i]);

    }
    pieces.insert({color::green, green_pieces_sprites});

    vector<Sprite> yellow_pieces_sprites;
    for (int i = 0; i < model.getBoard().getPieces(color::yellow).size() ; i++){
        yellow_pieces_sprites.push_back(Sprite(tPieces));
        yellow_pieces_sprites[i].setTextureRect(IntRect(0,0,30,30));
        yellow_pieces_sprites[i].setPosition((Vector2f) box2position[model.getBoard().getPiece(color::yellow, i)][i]);
    }
    pieces.insert({color::yellow, yellow_pieces_sprites});

    //Creación de los dados
    vector<color> colors = {red, blue, green, yellow};
    
    Vector2i ini_pos(850, 50);
    Vector2i offset(70,80);

    for (int i = 0; i < colors.size(); i++){
        for (int j = 1; j <= 6; j++){
            dices[colors[i]].push_back(DiceSprite(tDices, j, colors[i]));
            Vector2i pos = ini_pos + Vector2i((j-1)*offset.x, i*offset.y);
            dices[colors[i]][j-1].setPosition(pos.x, pos.y);
        } 
    }
}

void ParchisGUI::mainLoop(){
    processSettings();
    // processMouse();
    processEvents();
    processAnimations();
    paint();
}

void ParchisGUI::processEvents(){
    // Gestión de eventos (processEvents())
    Event event;
    while (game_window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            game_window.close();
        }

        if(event.type == Event::MouseButtonPressed){ // Eventos de ratón.
            //cout << pos.x << " " << pos.y << " " << world_pos.x << " " << world_pos.y << endl;
            //cout << board.getGlobalBounds().top << " " << board.getGlobalBounds().left << endl;
            if(event.mouseButton.button == Mouse::Left){
                //clicked = true;
                Vector2i pos = Mouse::getPosition(game_window);
                //world_pos = window.mapPixelToCoords(pos);
                vector<color> colors = {red, blue, green, yellow};
                for (int i = 0; i < colors.size(); i++){
                    for (int j = 0; j < dices[colors[i]].size(); j++){
                        DiceSprite *current_dice = &dices[colors[i]][j];
                        if(current_dice->getGlobalBounds().contains((Vector2f) pos)){ 
                            //animate_ficha = true;
                            cout << "Animacion " << i << " " << j << endl;
                            model->movePiece(current_dice->getModelColor(), 0, current_dice->getNumber());
                            vector<tuple<color, int, Box>> last_moves = model->getLastMoves();
                            for (int i = 0; i < last_moves.size(); i++){
                                Sprite *animate_sprite = &pieces[get<0>(last_moves[i])][get<1>(last_moves[i])];
                                Vector2f animate_pos = Vector2f(box2position[get<2>(last_moves[i])][0].x, box2position[get<2>(last_moves[i])][0].y);
                                SpriteAnimator animator = SpriteAnimator(*animate_sprite, animate_pos, 1000);
                                animations.push_back(animator);
                                // pieces[get<0>(last_moves[i])][get<1>(last_moves[i])].setPosition(box2position[get<2>(last_moves[i])][0].x, box2position[get<2>(last_moves[i])][0].y);
                            }

                            //animation_clock.restart();
                            //start_anim = ficha1.getPosition();
                        }
                    }
                }
                
            }
        }
    }
}

void ParchisGUI::processAnimations()
{
    list<SpriteAnimator>::iterator it;
    for (it = animations.begin(); it != animations.end();)
    {
        it->update();
        if(it->hasEnded()){
            it = animations.erase(it);
        }
        else{
            ++it;
        }
    }
}

void ParchisGUI::processSettings()
{
}

void ParchisGUI::paint(){
    game_window.clear(Color::White);

    // Vista del tablero (crear view más adelante)

    // Dibujar tablero
    game_window.draw(this->board);

    // Dibujar fichas
    // Rojas
    for(int i = 0; i < pieces.at(color::red).size(); i++)
    {
        game_window.draw(pieces.at(color::red).at(i));
    }
    // Azules
    for (int i = 0; i < pieces.at(color::blue).size(); i++)
    {
        game_window.draw(pieces.at(color::blue).at(i));
    }

    // Verdes
    for (int i = 0; i < pieces.at(color::green).size(); i++)
    {
        game_window.draw(pieces.at(color::green).at(i));
    }

    // Amarillas
    for (int i = 0; i < pieces.at(color::yellow).size(); i++)
    {
        game_window.draw(pieces.at(color::yellow).at(i));
    }

    //Dibujar dados
    // Rojas
    for(int i = 0; i < dices.at(color::red).size(); i++)
    {
        game_window.draw(dices.at(color::red).at(i));
    }
    // Azules
    for (int i = 0; i < dices.at(color::blue).size(); i++)
    {
        game_window.draw(dices.at(color::blue).at(i));
    }

    // Verdes
    for (int i = 0; i < dices.at(color::green).size(); i++)
    {
        game_window.draw(dices.at(color::green).at(i));
    }

    // Amarillas
    for (int i = 0; i < dices.at(color::yellow).size(); i++)
    {
        game_window.draw(dices.at(color::yellow).at(i));
    }

    game_window.display();
}

void ParchisGUI::run(){
    while(game_window.isOpen()){
        mainLoop();
    }
}