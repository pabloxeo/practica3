# include "Ninja.h"
# include "Parchis.h"
# include "AIPlayer.h"

void Ninja::think(color & c_piece,  int & id_piece, int & dice) const{
    // jeje
    AIPlayer::think(c_piece, id_piece, dice); // Nope ;)
}

void Ninja::setNinjaName(){
    switch(id){
        case 0:
            name = "¿Ninja 0? ¿Pero eso existe?";
            break;
        case 1:
            name = "Ninja 1: asequible?";
            break;
        case 2:
            name = "Ninja 2: una batalla de igual a igual.";
            break;
        case 3:
            name = "Ninja 3: el combate definitivo.";
            break;
        case 4:
            name = "Ninja 4: EL NINJA SECRETO. A lo mejor no deberías haberte metido aquí...";
            break;
        case -1:
        case -2:
        case -3:
        case -4:
            name = "A lo mejor no te compensa jugar conmigo. Soy malo y lento.";
            break;
        default:
            name = "Pero si yo solo pasaba por aquí...";
            break;
        
    }
}