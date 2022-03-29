# include "AIPlayer.h"
# include "Parchis.h"

bool AIPlayer::move(){
    color c_piece;
    int id_piece;
    int dice;
    think(c_piece, id_piece, dice);

    actual->movePiece(c_piece, id_piece, dice);
    return true;
}

void AIPlayer::think(color & c_piece, int & id_piece, int & dice) const{
    c_piece = actual->getCurrentColor();
    vector<int> current_dices;

    do{
        current_dices = actual->getAvailableDices(c_piece);
    }while(current_dices.size() == 0);

    dice = current_dices[rand() % current_dices.size()];
    
    vector<int> current_pieces;
    do{
        current_pieces = actual->getAvailablePieces(c_piece, dice);
    }while(current_pieces.size() == 0);

    id_piece = current_pieces[rand() % current_pieces.size()];
}

