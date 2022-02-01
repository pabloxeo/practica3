# include "ParchisGUI.h"

#define PI 3.14159265

void ParchisGUI::display()
{
    // El juego se crea dentro de la RenderWindow. Se le pasa tamaño, título y opciones (en este caso, que tenga barra de título y botón de cierre.)
    RenderWindow window(VideoMode(1600, 800), "SFML works!", Style::Titlebar | Style::Close);
    CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Cursor cursor;

    // Imágenes de texturas.
    Texture tBoard; // Textura del tablero de juego.
    tBoard.loadFromFile("data/textures/parchis_board_resized.png");

    Texture tFichas; // Textura para las fichas.
    tFichas.loadFromFile("data/textures/fichas_parchis_resized.png");

    Texture tDices; // Textura para los dados.
    tDices.loadFromFile("data/textures/dice1.png");
    //Se crean 6 dados
    Sprite dice1(tDices), dice2(tDices), dice3(tDices), dice4(tDices), dice5(tDices), dice6(tDices);
    dice1.setTextureRect(IntRect(2,120,120,120)); //Cara1
    dice1.setPosition(30,100);
    bool dice1_used = false;
    //dice1.setScale(0.5, 0.5);
    dice2.setTextureRect(IntRect(121,120,120,120)); //Cara2
    dice2.setPosition(150,100);
    bool dice2_used = false;
    //dice2.setScale(0.5, 0.5);
    dice3.setTextureRect(IntRect(237,120,120,120)); //Cara3
    dice3.setPosition(270,100);
    bool dice3_used = false;
    //dice3.setScale(0.5, 0.5);
    dice4.setTextureRect(IntRect(352,120,120,120)); //Cara4
    dice4.setPosition(390,100);
    bool dice4_used = false;
    //dice4.setScale(0.5, 0.5);
    dice5.setTextureRect(IntRect(468,120,120,120)); //Cara5
    dice5.setPosition(510,100);
    bool dice5_used = false;
    //dice5.setScale(0.5, 0.5);
    dice6.setTextureRect(IntRect(583,120,120,120)); //Cara6
    dice6.setPosition(630,100);
    bool dice6_used = false;
    //dice6.setScale(0.5, 0.5);

    //Fichas jugador azul
    Sprite ficha_b1(tFichas), ficha_b2(tFichas), ficha_b3(tFichas), ficha_b4(tFichas);
    load_player(color::blue, ficha_b1, ficha_b2, ficha_b3, ficha_b4);
    //Fichas jugador verde
    Sprite ficha_g1(tFichas), ficha_g2(tFichas), ficha_g3(tFichas), ficha_g4(tFichas);
    load_player(color::green, ficha_g1, ficha_g2, ficha_g3, ficha_g4);


    // Sprites, se generan a partir de una textura y es lo que se visualiza.
    Sprite board(tBoard); // Sprite del tablero.
    bool rotate_board = false; //Variables para rotar el tablero.
    float angle0 = 0.0;

    // Reloj para animaciones (por ejemplo, mover una ficha.)
    Clock animation_clock;


    //board.setScale(800.f/3740.f, 800.f/3740.f);

    // Pruebas de cursores. Se puede modificar el tipo de cursor (flecha, mano, reloj, ...) según sobre qué se encuentre el ratón.
    Image iCursorWait, iCursorThink, iCursorHand;
    iCursorThink.loadFromFile("data/cursors/hand_cursor_resized.png");

    Cursor cursorWait, cursorThink, cursorHand;
    cursorThink.loadFromPixels(iCursorThink.getPixelsPtr(), Vector2u(iCursorThink.getSize().x, iCursorThink.getSize().y), Vector2u(0, 0));

    // window.setMouseCursor(cursorThink);

    Sprite ficha1(tFichas); // Sprite para una ficha. Se harían tantos sprites como fichas haya, pero todos se montarían sobre la misma textura, la de las fichas.
    ficha1.setTextureRect(IntRect(0,30,30,30)); // La textura de las fichas contiene las fichas de todos los colores. Seleccionamos el rectángulo (esquina_x, esquina_y, largo, alto) con el color que nos interesa
    //ficha1.setScale(0.25, 0.25);
    int pos_ficha_x = 25;
    int pos_ficha_y = 305;
    ficha1.setPosition(pos_ficha_x, pos_ficha_y); // Posición del sprite dentro de la ventana.

    // Variables para el ejemplo de animación.
    bool animate_ficha = false;
    Vector2f start_anim, end_anim(385, 365);

    // Ejemplo para reproducir músca de fondo (clase Music).
    Music background_theme;
    const string background_theme_file = "data/music/background_theme";

    if(background_theme.openFromFile(background_theme_file + ".wav")){
        background_theme.setLoop(true); // Para reproducir en bucle.

        ifstream loop_file((background_theme_file + ".loop").c_str());
        if(loop_file.good()){
            float loop_start, loop_end;
            loop_file >> loop_start;
            loop_file >> loop_end;
            background_theme.setLoopPoints(Music::TimeSpan(seconds(loop_start), seconds(loop_end - loop_start))); // Se puede elegir los puntos exactos en los que cicle la música de fondo.
            cout << "Added loop points for background theme: " << loop_start << " " << loop_end << endl;
        }
        else cout << "No loop points found for background theme." << endl;

        background_theme.setVolume(100.f);
        background_theme.play();
    }

    // Ejemplo para reproducir sonidos Parte 1 (se cargan primero en SoundBuffer, parecido a lo que se hace con las texturas)
    int sound_id = 0;
    vector<SoundBuffer> sound_buffers;
    sound_buffers.resize(4);
    Sound sound;

    sound_buffers[0].loadFromFile("data/music/coin.wav");
    sound_buffers[1].loadFromFile("data/music/coin2.wav");
    sound_buffers[2].loadFromFile("data/music/explosion.wav");
    sound_buffers[3].loadFromFile("data/music/teleport.wav");

    // sound_buffers[4].loadFromFile("data/music/epic_win.wav");

    // Para girar el tablero (combinar con eventos de ratón)
    View view1(FloatRect(0.f, 0.f, 800.f, 800.f));
    view1.setViewport(FloatRect(0.f, 0.f, 0.5f, 1.0f));
    View view2(FloatRect(0.f, 0.f, 800.f, 800.f));
    view2.setViewport(FloatRect(0.5f, 0.f, 0.5f, 1.0f));

    //view1.setRotation(45.f);
    // view1.setRotation(angle);
    window.setView(view1);


    Vector2i pos = Mouse::getPosition(window);
    Vector2f world_pos = window.mapPixelToCoords(pos);
    bool clicked = false;
    Vector2i click_pos = Vector2i(0, 0);

    // Pruebas para la animación
    int casilla = 2;
    box_type bt = box_type::normal;
    color c = color::none;
    int cas_old = 1;
    box_type bt_old = box_type::normal;
    color c_old = color::none;

    cout << pos.x << " " << pos.y << endl;
    // cout << ficha1.getGlobalBounds() << endl;
    while(window.isOpen())
    {
        window.setView(view1);
        // Bucle principal. Se va refrescando en función de lo que ocurra en el juego.
        pos = Mouse::getPosition(window);
        world_pos = window.mapPixelToCoords(pos);

        Event event;
        // Gestión de colisiones (processCollisions()) para ver sobre qué está el ratón.
        if(ficha1.getGlobalBounds().contains((Vector2f) world_pos)){ // Ejemplo: si el ratón está sobre la ficha se ilumina.
            if (cursor.loadFromSystem(sf::Cursor::Hand))
                window.setMouseCursor(cursor);
            ficha1.setColor(Color::White);
        }
        else{
            ficha1.setColor(Color(128,128,128,255));


            if(board.getGlobalBounds().contains((Vector2f) world_pos)){
                if (cursor.loadFromSystem(sf::Cursor::Hand))
                    window.setMouseCursor(cursor);
            }
            else{
                if (cursor.loadFromSystem(sf::Cursor::Arrow))
                    window.setMouseCursor(cursor);

            }
        }
        // Gestión de eventos (processEvents())
        while(window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }
            // Ejemplo de manejo de teclas. En este caso desplaza la ficha según la dirección que se pulse. Creo que poca utilidad para el parchís.
            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Up){
                    pos_ficha_y -= 1;
                }
                if(event.key.code == Keyboard::Down){
                    pos_ficha_y += 1;
                }
                if(event.key.code == Keyboard::Left){
                    pos_ficha_x -= 1;
                }
                if(event.key.code == Keyboard::Right){
                    pos_ficha_x += 1;
                }
                ficha1.setPosition(pos_ficha_x, pos_ficha_y);
                cout << pos_ficha_x << " " << pos_ficha_y << endl;
            }

            if(event.type == Event::MouseButtonPressed){ // Eventos de ratón.
                cout << pos.x << " " << pos.y << " " << world_pos.x << " " << world_pos.y << endl;
                cout << board.getGlobalBounds().top << " " << board.getGlobalBounds().left << endl;
                if(event.mouseButton.button == Mouse::Left){
                    if(clicked==false){
                        clicked = true;
                        click_pos = pos;
                        if(ficha1.getGlobalBounds().contains((Vector2f) world_pos)){ // Ejemplo: Al clickar en la ficha se inicia la animación que la mueve.
                            animate_ficha = true;
                            animation_clock.restart();
                            start_anim = ficha1.getPosition();
                        }
                        else if(board.getGlobalBounds().contains((Vector2f) world_pos)){ // Ejemplo: al clickar sobre el tablero y arrastrar, se puede girar.
                            cout << "ESTOY EN PARCHIS" << endl;
                            rotate_board = true;
                            FloatRect board_box = board.getGlobalBounds();
                            Vector2f board_center(board_box.left + board_box.width / 2, board_box.top + board_box.height / 2);
                            angle0 =  atan2(pos.x - board_center.x, pos.y - board_center.y) * 180.f / PI;
                        }
                    }

                    // Ejemplo para reproducir sonidos Parte 2 (en este caso, con cada click)
                    sound.setBuffer(sound_buffers[sound_id]);
                    sound.play();
                    sound_id = (sound_id + 1) % sound_buffers.size();
                }
            }

            if(event.type == Event::MouseButtonReleased){ // Evento de soltar ratón. Se termina por ejemplo el giro de tablero.
                clicked = false;
                rotate_board = false;
            }
        }

        // Girar tablero si se activó en el evento.
        if(rotate_board){
            FloatRect board_box = board.getGlobalBounds();
            Vector2f board_center(board_box.left + board_box.width / 2, board_box.top + board_box.height / 2);

            float angle = atan2(pos.x - board_center.x, pos.y - board_center.y) * 180.f / PI;

            view1.rotate(angle - angle0);
            angle0 = angle;
            window.setView(view1);
        }
        animate_ficha = true;
        // Mover ficha (de forma animada) si se activó en el evento.
        if(animate_ficha){
            float t = animation_clock.getElapsedTime().asMilliseconds();
            // cout << t << endl;
            // cout << casilla << " " << bt << " " << c << endl;
            moveFichas(t, cas_old, bt_old, c_old, casilla, bt, c, ficha1);

            if(t > 1000){
                cas_old = casilla;
                bt_old = bt;
                c_old = c;
                switch(bt){
                case normal:
                    casilla = casilla + 1;
                    if(casilla > 68){
                        casilla = 1;
                        bt = final_queue;
                        c = blue;
                    }
                    break;
                case final_queue:
                    casilla = casilla + 1;
                    if(casilla > 7){
                        casilla = 1;
                        switch(c){
                            case blue:
                                c = red;
                                break;
                            case red:
                                c = green;
                                break;
                            case green:
                                c = yellow;
                                break;
                            case yellow:
                                c = blue;
                                bt = goal;
                                casilla = 0;
                                break;
                        }
                    }
                    break;

                case goal:
                    casilla = casilla + 1;
                    if(casilla > 0){
                        casilla = 0;
                        switch(c){
                            case blue:
                                c = red;
                                break;
                            case red:
                                c = green;
                                break;
                            case green:
                                c = yellow;
                                break;
                            case yellow:
                                c = blue;
                                bt = home;
                                break;
                        }
                    }
                    break;

                case home:
                    casilla = casilla + 1;
                    if(casilla > 0){
                        casilla = 0;
                        switch(c){
                            case blue:
                                c = red;
                                break;
                            case red:
                                c = green;
                                break;
                            case green:
                                c = yellow;
                                break;
                            case yellow:
                                c = none;
                                bt = normal;
                                casilla = 1;
                                break;
                        }
                    }
                    break;
                }
                //casilla = (casilla) % 68 + 1;
                //cout << casilla << endl;
                animation_clock.restart();
            }
            /*
            if(t > 1000){
                t = 1000;
                animate_ficha = false;
            }
            Vector2f new_ficha_position = (1.f - t/1000) * start_anim + (t/1000) * end_anim;
            ficha1.setPosition(new_ficha_position);
            */

        }



        // Se limpia la ventana y se redibujan los elementos.
        window.clear(Color::White);
        //window.draw(board);
        //window.draw(ficha1);
        // window.draw(shape);

        //Visualizamos fichas azules y verdes
        window.setView(view1);
        window.draw(board);
        window.draw(ficha1);
        window.draw(ficha_b1);
        window.draw(ficha_b2);
        window.draw(ficha_b3);
        window.draw(ficha_b4);
        window.draw(ficha_g1);
        window.draw(ficha_g2);
        window.draw(ficha_g3);
        window.draw(ficha_g4);

        window.setView(view2);
        world_pos = window.mapPixelToCoords(pos);
        //Control para el dado 1
        if (dice1_used){                        //El número 1 ya se ha usado --> se oculta
            dice1.setColor(Color(255,255,255,0));
        }
        else if(dice1.getGlobalBounds().contains((Vector2f) world_pos)){ // El ratón está sobre el número 1 --> se ilumina
            dice1.setColor(Color::White);
            if(event.type == Event::MouseButtonPressed){
                if(event.mouseButton.button == Mouse::Left){ //Se selecciona el número --> se mueve la ficha 1 posición
                    int ficha_b2_box = num_box((int)ficha_b2.getPosition().x, (int)ficha_b2.getPosition().y);
                    moveFichas(1000, ficha_b2_box, bt_old, c_old, ficha_b2_box+1, bt, c, ficha_b2);
                    dice1_used = true;
                }
            }
        }
        else{                                   //El número 1 se puede usar --> visible pero sin iluminar
            dice1.setColor(Color(200,200,200,255));
        }

        //Visualizamos dados
        window.setView(view2);
        window.draw(dice1);
        window.draw(dice2);
        window.draw(dice3);
        window.draw(dice4);
        window.draw(dice5);
        window.draw(dice6);

        window.display();
    }
}


void ParchisGUI::moveFichas(float t, int i, box_type bt, color c, Sprite & ficha1){
    Vector2f start_anim, end_anim;
    // cout << t << endl;
    // Clock animation_clock;


    // Texture tFichas; // Textura para las fichas.
    // tFichas.loadFromFile("data/textures/fichas_parchis_resized.png");

    // Sprite ficha1(tFichas); // Sprite para una ficha. Se harían tantos sprites como fichas haya, pero todos se montarían sobre la misma textura, la de las fichas.
    // ficha1.setTextureRect(IntRect(0,30,30,30)); // La textura de las fichas contiene las fichas de todos los colores. Seleccionamos el rectángulo (esquina_x, esquina_y, largo, alto) con el color que nos interesa
    // ficha1.setScale(0.25, 0.25);
    // int pos_ficha_x = 25;
    // int pos_ficha_y = 305;
    // ficha1.setPosition(box2position[{1, box_type::normal, color::none}][0].x, box2position[{1, box_type::normal, color::none}][0].y); // Posición del sprite dentro de la ventana.

    start_anim = (Vector2f) box2position[{i, bt, c}][0];
    end_anim = (Vector2f) box2position[{(i + 1) % 68 + 1, box_type::normal, color::none}][0];
    //for (int i = 2; i < 68; i++){
    // start_anim = ficha1.getPosition();
        // float t = animation_clock.getElapsedTime().asMilliseconds();
    if(t > 1000){
        t = 1000;
    }
    Vector2f new_ficha_position = (1.f - t/1000.f) * start_anim + (t/1000.f) * end_anim;
    ficha1.setPosition(new_ficha_position);
    //}
}

void ParchisGUI::moveFichas(float t, int i_orig, box_type bt_orig, color c_orig, int i_end, box_type bt_end, color c_end, Sprite & ficha1){
    Vector2f start_anim, end_anim;
    // cout << t << endl;
    // Clock animation_clock;


    // Texture tFichas; // Textura para las fichas.
    // tFichas.loadFromFile("data/textures/fichas_parchis_resized.png");

    // Sprite ficha1(tFichas); // Sprite para una ficha. Se harían tantos sprites como fichas haya, pero todos se montarían sobre la misma textura, la de las fichas.
    // ficha1.setTextureRect(IntRect(0,30,30,30)); // La textura de las fichas contiene las fichas de todos los colores. Seleccionamos el rectángulo (esquina_x, esquina_y, largo, alto) con el color que nos interesa
    // ficha1.setScale(0.25, 0.25);
    // int pos_ficha_x = 25;
    // int pos_ficha_y = 305;
    // ficha1.setPosition(box2position[{1, box_type::normal, color::none}][0].x, box2position[{1, box_type::normal, color::none}][0].y); // Posición del sprite dentro de la ventana.

    start_anim = (Vector2f) box2position[{i_orig, bt_orig, c_orig}][0];
    end_anim = (Vector2f) box2position[{i_end, bt_end, c_end}][0];
    //for (int i = 2; i < 68; i++){
    // start_anim = ficha1.getPosition();
        // float t = animation_clock.getElapsedTime().asMilliseconds();
    if(t > 1000){
        t = 1000;
    }
    Vector2f new_ficha_position = (1.f - t/1000.f) * start_anim + (t/1000.f) * end_anim;
    ficha1.setPosition(new_ficha_position);
    //}
}


void ParchisGUI::set_color(color my_color, Sprite & ficha){
    switch(my_color){
        case blue:
            ficha.setTextureRect(IntRect(0,30,30,30));
            break;
        case red:
            ficha.setTextureRect(IntRect(30,30,30,30));
            break;
        case green:
            ficha.setTextureRect(IntRect(30,0,30,30));
            break;
        case yellow:
            ficha.setTextureRect(IntRect(0,0,30,30));
            break;
    }
}

void ParchisGUI::load_player(color my_color, Sprite & ficha1, Sprite & ficha2, Sprite & ficha3, Sprite & ficha4){
    Vector2f pos_ficha1, pos_ficha2;
    if (my_color == color::red){
        pos_ficha1 = (Vector2f) box2position[{38, box_type::normal, color::none}][0];
        pos_ficha2 = (Vector2f) box2position[{51, box_type::normal, color::none}][0];
    }
    else if (my_color == color::yellow){
        pos_ficha1 = (Vector2f) box2position[{4, box_type::normal, color::none}][0];
        pos_ficha2 = (Vector2f) box2position[{17, box_type::normal, color::none}][0];
    }
    else if (my_color == color::green){
        pos_ficha1 = (Vector2f) box2position[{55, box_type::normal, color::none}][0];
        pos_ficha2 = (Vector2f) box2position[{68, box_type::normal, color::none}][0];
    }
    else if (my_color == color::blue){
        pos_ficha1 = (Vector2f) box2position[{21, box_type::normal, color::none}][0];
        pos_ficha2 = (Vector2f) box2position[{34, box_type::normal, color::none}][0];
    }
    Vector2f pos_ficha3 = (Vector2f) box2position[{0, box_type::home, my_color}][1];
    Vector2f pos_ficha4 = (Vector2f) box2position[{0, box_type::home, my_color}][3];
    set_color(my_color, ficha1);
    set_color(my_color, ficha2);
    set_color(my_color, ficha3);
    set_color(my_color, ficha4);
    ficha1.setPosition(pos_ficha1);
    ficha2.setPosition(pos_ficha2);
    ficha3.setPosition(pos_ficha3);
    ficha4.setPosition(pos_ficha4);
}

int ParchisGUI::num_box(int coord_x, int coord_y){
    int key = 0;
    //map<Piece, vector<Vector2i> >::iterator it;
    for (auto &i : box2position) {
      if (i.second[0] == Vector2i(coord_x, coord_y)) {
         key = i.first.num;
         break; // to stop searching
      }
    }
    return key;
}
