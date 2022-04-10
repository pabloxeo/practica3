# include "AIPlayer.h"
# include "Parchis.h"

bool AIPlayer::move(){
    cout << "HOLOO" << endl;
    color c_piece;
    int id_piece;
    int dice;
    think(c_piece, id_piece, dice);

    actual->movePiece(c_piece, id_piece, dice);
    return true;
}

void AIPlayer::think(color & c_piece, int & id_piece, int & dice) const{
    cout << "HOLAAAAA" << endl;
    c_piece = actual->getCurrentColor();
    vector<int> current_dices;
    vector<int> current_pieces;

    do{
        current_dices = actual->getAvailableDices(c_piece);
        // Siempre debería haber al menos un dado para escoger
        // Para un dado podría no haber fichas disponibles.
        // En ese caso se debería poder pasar turno (no implementado aún)

        dice = current_dices[rand() % current_dices.size()];
        current_pieces = actual->getAvailablePieces(c_piece, dice);
    }while(current_pieces.size() == 0);

    id_piece = current_pieces[rand() % current_pieces.size()];
}

