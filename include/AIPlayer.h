#ifndef __AI_PLAYER_H__
#define __AI_PLAYER_H__

# include "Attributes.h"
# include "Player.h"

class AIPlayer: public Player{
    private:
        
    public:
        inline AIPlayer(string name):Player(name){};
        /**
         * @brief Función abstracta que define el movimiento devuelto por el jugador.
         * 
         * @param dice 
         * @param id_piece 
         * @param c_piece 
         * @return true 
         * @return false 
         */
        virtual bool move();
        
        void think(color & c_piece,  int & id_piece, int & dice) const;



};
#endif