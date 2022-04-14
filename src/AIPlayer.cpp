# include "AIPlayer.h"
# include "Parchis.h"

bool AIPlayer::move(){
    cout << "Realizo un movimiento automatico" << endl;
    
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
    vector<int> current_pieces;

    current_dices = actual->getAvailableDices(c_piece);
    // Siempre debería haber al menos un dado para escoger
    // Para un dado podría no haber fichas disponibles.
    // En ese caso se puede pasar turno.
    dice = current_dices[rand() % current_dices.size()];
    current_pieces = actual->getAvailablePieces(c_piece, dice);
    // Si tengo fichas para el dado elegido muevo una al azar.
    if(current_pieces.size() > 0){
        id_piece = current_pieces[rand() % current_pieces.size()];
    }
    else{
        // Si no tengo fichas para el dado elegido, pasa turno.
        id_piece = SKIP_TURN;
    }

    /*
    do{
        current_dices = actual->getAvailableDices(c_piece);
        // Siempre debería haber al menos un dado para escoger
        // Para un dado podría no haber fichas disponibles.
        // En ese caso se debería poder pasar turno (no implementado aún)

        dice = current_dices[rand() % current_dices.size()];
        current_pieces = actual->getAvailablePieces(c_piece, dice);
    }while(current_pieces.size() == 0);

    id_piece = current_pieces[rand() % current_pieces.size()];
    */
}

