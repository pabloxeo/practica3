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
        Box final_box = Box(1 + (piece_box.num+ dice_number - 1) % 68, box_type::normal, color::none);
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
