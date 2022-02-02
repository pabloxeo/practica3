# include "ParchisGUI.h"

ParchisGUI::ParchisGUI(const Parchis &model)
    : game_window(VideoMode(1600, 800), "Parchís", Style::Titlebar | Style::Close)
{
    this->model = model;

    //Cargamos las texturas
    this->tPieces.loadFromFile("data/textures/fichas_parchis_resized.png");
    this->tBoard.loadFromFile("data/textures/parchis_board_resized.png");

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

}