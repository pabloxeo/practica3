#ifndef __BOARD_H__
#define __BOARD_H__

# include <vector>
# include <map>
# include "Attributes.h"

using namespace std;


class Board{
    private:
        map<color, vector<Box> > pieces;

    public:
        /**
         * @brief Default construct a new Board object
         * 
         */
        Board();

        /**
         * @brief Construct a new Board object
         * 
         * @param d 
         */
        Board (const map <color, vector <Box> > & b);


        /**
         * @brief Función que devuelve el Box correspondiente a la ficha en la posición "idx" del vector de fichas de color "c".
         * 
         * @param c 
         * @param idx 
         * @return Box 
         */
        const Box & getPiece(const color c, const int idx);

        /**
         * @brief Función que devuelve el vector de Box del color "c".
         * 
         * @param c 
         * @return Box 
         */
        const vector<Box> & getPieces(const color c);

        /**
         * @brief Función que mueve la ficha de la posición "idx" del vector de fichas de color "c" al box "final_box".
         * 
         * @param c 
         * @param idx 
         * @param final_box 
         */
        void movePiece(const color c, const int idx, const Box & final_box);
};


#endif