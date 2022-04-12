#ifndef __DICE_H__
#define __DICE_H__

# include <vector>
# include <map>
# include "Attributes.h"

using namespace std;

class Dice{
    private:
        /**
         * @brief The dices for each player. The dices are grouped by layers.
         * First layer contains the classic 1-6 dices.
         * New layers can be added to force special values, like move 10 or 20.
         * 
         */
        map <color, vector<vector <int>> > dice;        
    
    public:
        /**
         * @brief Default construct a new Dice object
         * 
         */
        Dice();

        /**
         * @brief Construct a new Dice object
         * 
         * @param d 
         */
        Dice (const map <color, vector<vector <int> >> & d);

        /**
         * @brief Devuelve el dado para un cierto jugador "player".
         * 
         * @param player 
         * @return const vector<int>& 
         */
        const vector<int> & getDice (color player) const;

        /**
         * @brief Get the All Dice Layers object
         * 
         * @param player 
         * @return const vector<vector<int>>& 
         */
        const vector<vector<int>> & getAllDiceLayers(color player) const;

        /**
         * @brief Get the All Dice Layers object
         * 
         * @param player 
         * @return const vector<vector<int>>& 
         */
        const int getLayersSize(color player) const;

        /**
         * @brief Elimina el número "n" del dado del jugador "player".
         * 
         * @param player 
         * @param n 
         */
        void removeNumber (color player, int n);

        /**
         * @brief Resetear el dado del jugador "player" por el dado "new_dice". Default <1,2,3,4,5,6>.
         * 
         * @param player 
         * @param new_dice 
         */
        void resetDice (color player , const vector<int> & new_dice = {1,2,3,4,5,6});

        /**
         * @brief Función que comprueba si el número "n" está en el dado del jugador "player".
         * 
         * @param player 
         * @param n 
         * @return true 
         * @return false 
         */
        bool isAvailable(color player, int n) const;

        /**
         * @brief Función que añade un valor al dado del jugador "player".
         * 
         */
        void addNumber(color player, int n);

        /**
         * @brief Fuerza que el próximo número de dado del jugador "player" sea (únicamente) "n".
         * 
         * @param player 
         * @return int 
         */
        void forceNumber(color player, int n);
};

#endif