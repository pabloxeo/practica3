#include "Parchis.h"

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

bool Parchis::isLegalMove(color player, const Box & box, int dice_number){
    // Controlar si barreras, si está en la casa el movimiento solo sería legal si dice_number == 5, ...
    if (box.type == home && dice_number != 5){
        return false;
    }else if(box.type == goal){
        return false;
    }
    return true;
}

const vector<int> & Parchis::getAvailablePieces(color player, int dice_number){
    vector<Box> player_pieces = board.getPieces(player);
    vector<int> available_pieces;

    for(int i = 0; i < player_pieces.size(); i++){
        if(isLegalMove(player, player_pieces[i], dice_number)){
            available_pieces.push_back(i);
        }
    }

    return available_pieces;

}

void Parchis::movePiece(color player, int piece, int dice_number){
    // Switch por colores
    Box piece_box = board.getPiece(player, piece);
    if(isLegalMove(player, piece_box, dice_number)){
        Box final_box;
        cout << piece_box.num + dice_number << endl;

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

        if (piece_box.type == home){
            switch (player){
                case red:
                    final_box = Box(38, normal, none);
                    break;
                case blue:
                    final_box = Box(21, normal, none);
                    break;
                case yellow:
                    final_box = Box(4, normal, none);
                    break;
                case green:
                    final_box = Box(55, normal, none);
                    break;
            }
               
        }else if(piece_box.num <= 17 && piece_box.num + dice_number > 17 && player == blue && piece_box.type == normal){
            final_box = Box(piece_box.num + dice_number-17, final_queue, blue);

        }else if(piece_box.num <= 34 && piece_box.num + dice_number > 34 && player == red && piece_box.type == normal){
            final_box = Box(piece_box.num + dice_number-34, final_queue, red);

        }else if(piece_box.num <= 51 && piece_box.num + dice_number > 51 && player == green && piece_box.type == normal){
            final_box = Box(piece_box.num + dice_number-51, final_queue, green);

        }else if(piece_box.num <= 68 && piece_box.num + dice_number > 68 && player == yellow && piece_box.type == normal){
            final_box = Box(piece_box.num + dice_number-68, final_queue, yellow);

        }else if(piece_box.type == final_queue){
            if (piece_box.num + dice_number <= 7){
                final_box = Box(piece_box.num + dice_number, final_queue, player);
            }else if (piece_box.num + dice_number == 8){
                final_box = Box(0, goal, player);
            }else{
                final_box = Box(16 - (piece_box.num + dice_number), final_queue, player);
            }
        }
        else{
            final_box = Box(1 + (piece_box.num+ dice_number - 1) % 68, box_type::normal, color::none);
        }

        board.movePiece(player, piece, final_box);

        this->last_dice = dice_number;
        this->last_moves.clear();
        this->last_moves.push_back(tuple<color, int, Box>(player, piece, final_box));
        // Controlar si se come alguna ficha. En ese caso se actualiza también la ficha comida.
        // La ficha comida se añadiría también al vector last_moves.
    }
}

const vector<tuple<color, int, Box>> & Parchis::getLastMoves(){
    return this->last_moves;
}

int Parchis::getLastDice(){
    return this->last_dice;
}
