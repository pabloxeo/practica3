#ifndef __GUI_PLAYER_H__
#define __GUI_PLAYER_H__

# include "Attributes.h"
# include "AIPlayer.h"
# include <iostream>
using namespace std;

class GUIPlayer: public AIPlayer{
    private:
        bool auto_think;        
    public:
        inline GUIPlayer(string name):AIPlayer(name), auto_think(false){};

        /**
         * @brief Función abstracta que define el movimiento devuelto por el jugador.
         * 
         * @param dice 
         * @param id_piece 
         * @param c_piece 
         * @return true 
         * @return false 
         */
        bool move();

        inline bool isAutoThinking() const{
            return auto_think;
        }

        inline void setAutoThinking(bool auto_think){
            this->auto_think = auto_think;
        }

};
#endif