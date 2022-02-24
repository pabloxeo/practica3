#include "Parchis.h"

const vector<int> Parchis::safe_boxes = {4, 13, 17, 21, 30, 34, 38, 47, 51, 55, 64, 68};

Parchis::Parchis(){
    this->board = Board();
    this->dice = Dice();

    this->last_dice = -1;
    // last_moves vacío por defecto.
}

Parchis::Parchis(const Board & b, const Dice & d){
    this->board = board;
    this->dice = dice;

    this->last_dice = -1;
    // last_moves vacío por defecto.
}

const vector<int> & Parchis::getDice(color player){
    return dice.getDice(player);
}

const Board & Parchis::getBoard() const{
    return this->board;
}

const color Parchis::isWall(const Box & b) const{
    const vector<pair <color, int>> occupation = boxState(b);
    if (occupation.size() == 2 && occupation.at(0).first == occupation.at(1).first){
        return  occupation.at(0).first;
    }else{
        return none;
    }
}

const vector<color> Parchis::anyWall(const Box & b1, const Box & b2) const{
    Box final_box;
    if (b2.type == final_queue){
        switch (b2.col){
            case blue:
                final_box = Box(final_blue_box, normal, none);
            break;
            case red:
                final_box = Box(final_red_box, normal, none);
            break;
            case green:
                final_box = Box(final_green_box, normal, none);
            break;
            case yellow:
                final_box = Box(final_yellow_box, normal, none);
            break;
        }
    }else{
        final_box = b2;
    }

    vector<color> walls;
    if (b1.type != home){
        for (int i = b1.num+1; i <= final_box.num; i++){
            color c = isWall(Box(i, normal, none));
            if(c != none){
                walls.push_back(c);
            }
        }
    }
    return walls;
}

bool Parchis::isLegalMove(color player, const Box & box, int dice_number){
    Box final_box = computeMove(player, box, dice_number);
    // Controlar si barreras, si está en la casa el movimiento solo sería legal si dice_number == 5, ...
    if (box.type == home && dice_number != 5){
        return false;
    //Controlar que ya estés en el objetivo
    }else if(box.type == goal){
        return false;
    
    }else if(final_box.type != goal && final_box.type != home &&  boxState(final_box).size() == 2){
    //Controlar los muros
        return false;
    }else{
        vector<color> walls = anyWall(box, final_box);
        for (int i = 0; i < walls.size(); i++){
            cout << walls.at(i) << endl;
            if (walls.at(i) != player){
                return false;
            }
        }
    }
    return true;
}

const vector<int> Parchis::getAvailablePieces(color player, int dice_number){
    vector<Box> player_pieces = board.getPieces(player);
    vector<int> available_pieces;

    for(int i = 0; i < player_pieces.size(); i++){
        if(isLegalMove(player, player_pieces[i], dice_number)){
            available_pieces.push_back(i);
        }
    }

    return available_pieces;

}

const Box Parchis::computeMove(color player, const Box & piece_box, int dice_number) const{
    Box final_box;

    //Si sale un 6, comprobar si se da condición para avanzar 7 o 6
    if(dice_number == 6){
        bool pieces_out = true;
        for (int i = 0; i < board.getPieces(player).size() && pieces_out; i++){
            if (board.getPieces(player).at(i).type == home){
                pieces_out = false;
            }
        }

        if (pieces_out){
            dice_number = 7;
        }
    }

    //Si sale de la casilla de home
    if (piece_box.type == home){
        switch (player){
            case red:
                final_box = Box(init_red_box, normal, none);
                break;
            case blue:
                final_box = Box(init_blue_box, normal, none);
                break;
            case yellow:
                final_box = Box(init_yellow_box, normal, none);
                break;
            case green:
                final_box = Box(init_green_box, normal, none);
                break;
        }
            
    //Condiciones para empezar a avanzar por pasillo de meta
    }else if(piece_box.num <= 17 && piece_box.num + dice_number > 17 && player == blue && piece_box.type == normal){
        final_box = Box(piece_box.num + dice_number-17, final_queue, blue);

    }else if(piece_box.num <= 34 && piece_box.num + dice_number > 34 && player == red && piece_box.type == normal){
        final_box = Box(piece_box.num + dice_number-34, final_queue, red);

    }else if(piece_box.num <= 51 && piece_box.num + dice_number > 51 && player == green && piece_box.type == normal){
        final_box = Box(piece_box.num + dice_number-51, final_queue, green);

    }else if(piece_box.num <= 68 && piece_box.num + dice_number > 68 && player == yellow && piece_box.type == normal){
        final_box = Box(piece_box.num + dice_number-68, final_queue, yellow);

    //Si ya está en pasillo de meta
    }else if(piece_box.type == final_queue){
        if (piece_box.num + dice_number <= 7){
            final_box = Box(piece_box.num + dice_number, final_queue, player);
        }else if (piece_box.num + dice_number == 8){
            final_box = Box(0, goal, player);
        }else{
            final_box = Box(16 - (piece_box.num + dice_number), final_queue, player);
        }
    }
    //Por defecto
    else{
        final_box = Box(1 + (piece_box.num+ dice_number - 1) % 68, box_type::normal, color::none);
    }

    return final_box;
}

void Parchis::movePiece(color player, int piece, int dice_number){
    // Switch por colores
    Box piece_box = board.getPiece(player, piece);
    if(isLegalMove(player, piece_box, dice_number)){
        Box final_box = computeMove(player, piece_box, dice_number);

        /* Gestión de las "comidas"*/
        //Comprobar si hay una ficha en la casilla destino
        vector<pair <color, int>> box_states = boxState(final_box);
        bool hay_comida_xd = false;
        if (!box_states.empty() && box_states[0].first != player){
            //Comprobar que la casilla no es segura
            vector<int>::const_iterator ci; 
            if (final_box.type == normal && count(safe_boxes.begin(), safe_boxes.end(), final_box.num) == 0){
                //Movemos la ficha
                hay_comida_xd = true;

            }
        }


        board.movePiece(player, piece, final_box);

        this->last_dice = dice_number;
        this->last_moves.clear();
        this->last_moves.push_back(tuple<color, int, Box>(player, piece, final_box));

        // Controlar si se come alguna ficha. En ese caso se actualiza también la ficha comida.
        // La ficha comida se añadiría también al vector last_moves.
        if(hay_comida_xd){
            board.movePiece(box_states[0].first, box_states[0].second, Box(0, home, box_states[0].first));
            this->last_moves.push_back(tuple<color, int, Box>(box_states[0].first, box_states[0].second, Box(0, home, box_states[0].first)));
        }
    }
}

const vector<tuple<color, int, Box>> & Parchis::getLastMoves(){
    return this->last_moves;
}

int Parchis::getLastDice(){
    return this->last_dice;
}

const vector<pair <color, int>> Parchis::boxState(const Box & box) const{

    vector<pair <color, int>> occupation;

    for (int c = color::blue; c < color::none; c++){
        color col = (color)c;
        for (int i = 0; i < board.getPieces(col).size(); i++){
            if (board.getPiece(col, i) == box ){
                occupation.push_back(pair<color, int>(col, i));
            }
        }
    }

    return occupation;
}