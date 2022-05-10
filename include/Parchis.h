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
#include <memory>

// Macro que define el parámetro para indicar que no se mueve ficha.
#define SKIP_TURN -9999

using namespace std;

class Player;

class Parchis{
    private:
        //Tablero y dados
        Board board;
        Dice dice;

        //Variables para almacenar los últimos movimientos
        vector<tuple <color, int, Box, Box>> last_moves;
        tuple <color, int, int> last_action;
        int last_dice;

        //Turno actual
        int turn;
        
        //Jugadores del juego y jugadores y colorores actuales
        //0: yellow & red, 1: blue and green.
        int current_player;
        color current_color;
        vector <shared_ptr<Player>> players;
        vector <shared_ptr<Player>> viewers;

        //Variables para controlar acciones de los jugadores
        int illegal_move_player;
        int disconnected_player;

        //Booleanos para recordar movimientos especiales
        bool eating_move;
        bool goal_move;
        bool goal_bounce;
        bool remember_6;

        //Definición de casillas especiales
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
         * @deprecated Los jugadores se deben pasar desde fuera.
         * 
         */
        Parchis();

        /**
         * @brief Construct a new Parchis object
         * @deprecated Los jugadores se deben pasar desde fuera.
         *
         * @param b
         */
        Parchis(const BoardConfig &b);

        /**
         * @brief Construct a new Parchis object
         * @deprecated Los jugadores se deben pasar desde fuera.
         * 
         * @param b 
         * @param d 
         */
        Parchis(const Board & b, const Dice & d);

        /**
         * @brief Construct a new Parchis object
         * @deprecated Los jugadores se deben pasar desde fuera.
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
        Parchis(const BoardConfig &b, const Dice &d, shared_ptr<Player> p1,  shared_ptr<Player> p2);

        /**
         * @brief Construct a new Parchis object
         *
         * @param b
         * @param p1
         * @param p2
         */
        Parchis(const BoardConfig &b, shared_ptr<Player> p1,  shared_ptr<Player> p2);

        inline void addViewer(shared_ptr<Player> p){viewers.push_back(shared_ptr<Player>(p));}

        bool operator==(const Parchis & parchis) const;

        /**
         * @brief Get the Dice object
         * 
         * @param player 
         * @return const vector<int>& 
         */
        const Dice & getDice () const;


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
        inline const vector<int> getAvailableDices (color player) const{
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
        const vector<tuple <color, int, Box, Box>> & getLastMoves() const;

        /**
         * @brief Get the Last Action object
         * 
         * @return int 
         */
        inline const tuple <color, int, int> & getLastAction() const{
            return last_action;
        }

        inline const int getTurn() const{
            return turn;
        }


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

        inline const bool goalBounce() const{
            return goal_bounce;
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
         * @brief Función para comprobar que todos los jugadpres están listos para pasar el turno, y si no esperarlos.
         *
         */
        void waitForPlayers() const;

        /**
         * @brief Get the Current Player object
         * 
         * @return int 
         */
        inline int getCurrentPlayerId() const{
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

        inline vector<shared_ptr<Player>> & getPlayers(){
            return players;
        }

        /**
         * @brief Get the Current Color object
         * 
         * @return color 
         */
        inline color getCurrentColor() const{
            return this->current_color;
        }

        /**
         * @brief Indica si la partida ha terminado.
         * 
         * @return true 
         * @return false 
         */
        bool gameOver() const;

        void endGame();
        
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

        /**
         * @brief Devuelve el número de fichas de un color que han llegado a la meta.
         * 
         * @return int 
         */
        int piecesAtGoal(color player) const;

        /**
         * @brief Función que devuelve la distancia a la meta del color "player" desde
         * la casilla "box". 
         * 
         * @param player 
         * @param box 
         * @return int 
         */
        int distanceToGoal(color player, const Box & box) const;

        /**
         * @brief Función que devuelve la distancia a la meta de la ficha identificada
         * por id_piece del jugador identificado por player.
         * 
         * @param player 
         * @param id_piece
         * @return int 
         */
        int distanceToGoal(color player, int id_piece) const;

        /**
         * @brief Función que genera el siguiente movimiento siguiendo un orden 
         * ascendente de los dados.
         * 
         * @param c_piece 
         * @param id_piece 
         * @param dice 
         * @return Parchis 
         */
        Parchis generateNextMove(color & c_piece,  int & id_piece, int & dice) const;

        /**
         * @brief Función que genera el siguiente movimiento siguiendo un orden 
         * descendente de los dados.
         * 
         * @param c_piece 
         * @param id_piece 
         * @param dice 
         * @return Parchis 
         */
        Parchis generateNextMoveDescending(color & c_piece,  int & id_piece, int & dice) const;

        /**
         * @brief Función que devuelve si una determinada casilla es segura o no.
         * 
         * @param box 
         * @return true 
         * @return false 
         */
        bool isSafeBox(const Box & box) const;

        /**
         * @brief Función que devuelve si una determinada ficha de un determinado está
         * en una casilla segura o no.
         * 
         * @param player 
         * @param piece 
         * @return true 
         * @return false 
         */
        bool isSafePiece(const color & player, const int & piece) const;

        /**
         * @brief Función que devuelve el color de la barrera (en caso de haberla) en la casilla "b".
         * Es decir, si en la casilla "b" hay dos fichas de un mismo color devuelve este color.
         * 
         * @param b 
         * @return const color 
         */
        const color isWall(const Box & b) const;

        /**
         * @brief Función que devuelve el vector de colores de las barreras (en caso de haberlas) del
         * camino entre b1 y b2.
         * 
         * Esto es, se va recorriendo todas las casillas que habría que recorrer para ir de b1 y b2,
         * y siempre que se encuentran dos fichas de un mismo color en una misma casilla se añade ese
         * color al vector que se devuelve.
         * 
         * Por ejemplo: si en la casilla 2 hay una barrera amarilla y en la 4 una azul, el anywalls(1,6) 
         * devuelve {yellow, blue}
         * 
         * @param b1 
         * @param b2 
         * @return const vector<color> 
         */
        const vector<color> anyWall(const Box & b1, const Box & b2) const;

        vector<color> getPlayerColors(int player) const;


};


#endif 