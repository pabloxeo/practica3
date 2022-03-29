#ifndef __GUI_PLAYER_H__
#define __GUI_PLAYER_H__

# include "Attributes.h"
# include "AIPlayer.h"



class GUIPlayer: public AIPlayer{        
    public:
        inline GUIPlayer(string name):AIPlayer(name){};

        /**
         * @brief Función abstracta que define el movimiento devuelto por el jugador.
         * 
         * @param dice 
         * @param id_piece 
         * @param c_piece 
         * @return true 
         * @return false 
         */
        inline bool move(){return false;}

};
#endif