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

        /**
         * @brief Heurística de prueba para validar el algoritmo de búsqueda.
         * 
         * @param estado Instancia de Parchis con el estado actual de la partida.
         * @param jugador Id del jugador actual (0 o 1)
         * @return double 
         */
        static double ValoracionTest(const Parchis &estado, int jugador);

        /**
         * @brief Propuesta de declaración de la función poda alfa-beta.
         * La propuesta es solo sugerencia, los parámetros de la declaración podrían variar.
         */
        //double Poda_AlfaBeta(const Parchis &actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece, int &dice, double alpha, double beta, double (*heuristic)(const Parchis &, int)) const;
};
#endif