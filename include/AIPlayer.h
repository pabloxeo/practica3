#ifndef __AI_PLAYER_H__
#define __AI_PLAYER_H__

# include "Attributes.h"
# include "Player.h"

class AIPlayer: public Player{
    protected:
        //Id identificativo del jugador
        int id;
    public:
        /**
         * @brief Constructor de un objeto AIPlayer
         * 
         * @param name 
         */
        inline AIPlayer(const string & name):Player(name), id(0){};
        
        /**
         * @brief Constructor de un objeto AIPlayer 
         * 
         * @param name 
         * @param id 
         */
        inline AIPlayer(const string & name, int id):Player(name), id(id){};

        inline virtual void perceive(Parchis &p){Player::perceive(p);}

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
        
        virtual void think(color & c_piece,  int & id_piece, int & dice) const;

        inline virtual bool canThink() const{return true;}

};
#endif