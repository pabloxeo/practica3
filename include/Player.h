#ifndef __PLAYER_H__
#define __PLAYER_H__

# include "Attributes.h"

class Player{
    private:
        string name;
    public:
        inline Player(string name){this->name = name;}

        /**
         * @brief Función abstracta que define el movimiento devuelto por el jugador.
         * 
         * @param dice 
         * @param id_piece 
         * @param c_piece 
         * @return true 
         * @return false 
         */
        virtual bool move(color & c_piece,  int & id_piece, int & dice) = 0;

};
#endif