#ifndef __PARCHIS_H__
#define __PARCHIS_H__

# include <tuple>
# include "Dice.h"
# include "Board.h"
#include <iostream>

using namespace std;

class Parchis{
    private:
        Board board;
        Dice dice;
        vector<tuple <color, int, Box>> last_moves;
        int last_dice;

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
        const vector<int> & getAvailablePieces (color player, int dice_number);

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

};


#endif 