#ifndef __NINJA__
#define __NINJA__

# include "Attributes.h"
# include "AIPlayer.h"


class Ninja: public AIPlayer{
    public:
        /**
         * @brief Constructor de un objeto Ninja con id por defecto
         * 
         * @param name 
         */
        inline Ninja(const string & name):AIPlayer(name){};

        /**
         * @brief Constructor de un objeto Nina especificando id
         * 
         * @param name 
         * @param id 
         */
        inline Ninja(const string & name, int id):AIPlayer(name, id){};
        
        /**
         * @brief Función que se encarga de decidir el mejor movimiento posible a 
         * partir del estado actual del tablero. Asigna a las variables pasadas por
         * referencia el valor de color de ficha, id de ficha y dado del mejor movimiento.
         * 
         * @param c_piece Color de la ficha
         * @param id_piece Id de la ficha
         * @param dice Número de dado
         */
        void think(color & c_piece,  int & id_piece, int & dice) const;
};

#endif