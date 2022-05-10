# include "Ninja.h"
# include "Parchis.h"
# include "AIPlayer.h"

//const double masinf=9999999999.0, menosinf=-9999999999.0;
//const double val_masinf=99999999.0, val_menosinf=-99999999.0;
//const int num_pieces = 4;
//const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
//const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

void Ninja::think(color & c_piece,  int & id_piece, int & dice) const{
    // jeje
    AIPlayer::think(c_piece, id_piece, dice); // Nope ;)
}