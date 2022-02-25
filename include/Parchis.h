#ifndef __PARCHIS_H__
#define __PARCHIS_H__

# include <tuple>
# include "Dice.h"
# include "Board.h"
#include <iostream>
#include <algorithm>


using namespace std;

class Parchis{
    private:
        Board board;
        Dice dice;
        vector<tuple <color, int, Box>> last_moves;
        int last_dice;

        static const int final_red_box = 34;
        static const int final_blue_box = 17;
        static const int final_green_box = 51;
        static const int final_yellow_box = 68;

        static const int init_red_box = 38;
        static const int init_blue_box = 21;
        static const int init_green_box = 55;
        static const int init_yellow_box = 4;

        static const vector<int> safe_boxes;

    public:
        /**
         * @brief Default construct a new Parchis object
         * 
         */
        Parchis();

        /**
         * @brief Construct a new Parchis object
         * 
         * @param b 
         * @param d 
         */
        Parchis(const Board & b, const Dice & d);

        /**
         * @brief Get the Dice object
         * 
         * @param player 
         * @return const vector<int>& 
         */
        const vector<int> & getDice (color player);


         /**
         * @brief Get the Board object
         * 
         * @param player 
         * @return const vector<int>& 
         */
        const Board & getBoard () const;

        /**
         * @brief Get the Available Pieces object
         * 
         * @param player 
         * @param dice_number 
         * @return const vector<int>& 
         */
        const vector<int> getAvailablePieces (color player, int dice_number);

        /**
         * @brief Mover la pieza número "piece" del jugador "player" "dice_number" posiciones.
         * 
         * @param player 
         * @param piece 
         * @param dice_number 
         */
        void movePiece(color player, int piece, int dice_number);

        /**
         * @brief Comprobar si un movimiento es válido.
         * 
         * @param player 
         * @param box 
         * @param dice_number 
         * @return true 
         * @return false 
         */
        bool isLegalMove(color player, const Box & box, int dice_number);

        /**
         * @brief Get the Last Moves object
         * 
         * @return const vector<tuple <color, int, Box>>& 
         */
        const vector<tuple <color, int, Box>> & getLastMoves();


        /**
         * @brief Get the Last Dice object
         * 
         * @return int 
         */
        int getLastDice();

        /**
         * @brief Obtener la ocupación de un box
         * 
         * @param box 
         * @return vector<pair <color, int>> 
         */
        const vector<pair <color, int>> boxState(const Box & box) const;

        /**
         * @brief Función que devuelve el color del muro (en caso de haberlo) en la casilla "box"
         * 
         * @param b 
         * @return const color 
         */
        const color isWall(const Box & b) const;

        /**
         * @brief Función que devuelve el vector de colores de los muros (en caso de haberlos) del
         * camino entre b1 y b2.
         * 
         * @param b1 
         * @param b2 
         * @return const vector<color> 
         */
        const vector<color> anyWall(const Box & b1, const Box & b2) const;

        /**
         * @brief Función auxiliar que calcula la casilla destino tras aplicar el movimiento.
         * 
         * @param player 
         * @param box 
         * @param dice_number 
         * @return const Box 
         */
        const Box computeMove(color player, const Box & box, int dice_number, bool * goal_bounce = NULL) const;
};


#endif 