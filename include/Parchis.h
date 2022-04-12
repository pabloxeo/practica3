#ifndef __PARCHIS_H__
#define __PARCHIS_H__

# include <tuple>
# include "Dice.h"
# include "Board.h"
# include "GUIPlayer.h"
# include "Player.h"
# include "AIPlayer.h"
#include <iostream>
#include <algorithm>

// Macro que define el parámetro para indicar que no se mueve ficha.
#define SKIP_TURN -1

using namespace std;

class Player;

class Parchis{
    private:
        Board board;
        Dice dice;
        vector<tuple <color, int, Box, Box>> last_moves;
        int last_dice;
        
        //0: yellow & red, 1: blue and green.
        int current_player;
        color current_color;
        vector <Player*> players;

        int illegal_move_player;

        bool eating_move;
        bool goal_move;

        static const int final_red_box = 34;
        static const int final_blue_box = 17;
        static const int final_green_box = 51;
        static const int final_yellow_box = 68;

        static const int init_red_box = 38;
        static const int init_blue_box = 21;
        static const int init_green_box = 55;
        static const int init_yellow_box = 4;

        static const vector<int> safe_boxes;

        static const map<color, int> final_boxes;
        static const map<color, int> init_boxes;

        /**
         * @brief
         *
         */
        void nextTurn();

    public:
        static const vector<color> game_colors;
        
        /**
         * @brief Default construct a new Parchis object
         * 
         */
        Parchis();

        /**
         * @brief Construct a new Parchis object
         * 
         * @param b 
         */
        Parchis(const BoardConfig &b);

        /**
         * @brief Construct a new Parchis object
         * 
         * @param b 
         * @param d 
         */
        Parchis(const Board & b, const Dice & d);

        /**
         * @brief Construct a new Parchis object
         * 
         * @param b 
         * @param d 
         */
        Parchis(const BoardConfig & b, const Dice & d);

        /**
         * @brief Construct a new Parchis object
         * 
         * @param b 
         * @param d 
         * @param p1 
         * @param p2 
         */
        Parchis(const Board & b, const Dice & d, Player & p1, Player & p2);

        /**
         * @brief Construct a new Parchis object
         * 
         * @param b 
         * @param d 
         * @param p1 
         * @param p2 
         */
        Parchis(const BoardConfig &b, const Dice &d, Player &p1, Player &p2);

        /**
         * @brief Get the Dice object
         * 
         * @param player 
         * @return const vector<int>& 
         */
        const Dice & getDice ();


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
        const vector<int> getAvailablePieces (color player, int dice_number) const;

        /**
         * @brief Get the Available Dices object
         * 
         * @param player 
         * @param dice_number 
         * @return const vector<int>& 
         */
        inline const vector<int> getAvailableDices (color player){
            return dice.getDice(player);
        }

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
        bool isLegalMove(color player, const Box & box, int dice_number) const;

        /**
         * @brief Comprobar si el jugador puede pasar turno con el dado seleccionado (si no tiene fichas para mover).
         * 
         * @param player 
         * @param dice_number 
         * @return true 
         * @return false 
         */
        bool canSkipTurn(color player, int dice_number) const;

        /**
         * @brief Get the Last Moves object
         * 
         * @return const vector<tuple <color, int, Box>>& 
         */
        const vector<tuple <color, int, Box, Box>> & getLastMoves();


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

        /**
         * @brief Get the eating_move object
         *
         * 
         */

        inline const bool isEatingMove() const {
            return eating_move;
        }

        /**
         * @brief Get the goal_move object
         *
         * 
         */

        inline const bool isGoalMove() const {
            return goal_move;
        }


        /**
         * @brief 
         * 
         */
        void gameLoop();


        /**
         * @brief 
         * 
         */
        bool gameStep();

        /**
         * @brief Get the Current Player object
         * 
         * @return int 
         */
        inline int getCurrentPlayerId(){
            return current_player;
        }

        /**
         * @brief Get the Current Player object
         * 
         * @return Player& 
         */
        inline Player & getCurrentPlayer(){
            return *players[current_player];
        }

        /**
         * @brief Get the Current Color object
         * 
         * @return color 
         */
        inline color getCurrentColor(){
            return this->current_color;
        }

        /**
         * @brief Indica si la partida ha terminado.
         * 
         * @return true 
         * @return false 
         */
        bool gameOver() const;
        
        /**
         * @brief Si la partida ha terminado, devuelve el índice del jugador ganador (0 o 1).
         * 
         * @return int 
         */
        int getWinner() const;

        /**
         * @brief Si la partida ha terminado, devuelve el color del jugador ganador.
         * 
         * @return color 
         */
        color getColorWinner() const;

        /**
         * @brief Devuelve true si y solo si uno de los jugadores ha hecho un movimiento ilegal.
         * El jugador que ha hecho dicho movimiento pierde automáticamente.
         * 
         * @return true 
         * @return false 
         */
        bool illegalMove() const;
};


#endif 