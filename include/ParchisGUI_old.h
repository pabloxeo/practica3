#ifndef __PARCHISGUI_H__
#define __PARCHISGUI_H__

# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include <iostream>
# include <math.h>
# include <fstream>
# include "Board.h"
# include "Attributes.h"

using namespace sf;
using namespace std;

class ParchisGUI{
    private:
    map<Box, vector<Vector2i> > box2position{
    //Definición de las casillas normales
    //Para cada casilla definimos 3 posiciones: (1) En el centro de la casilla, (2) y (3) a ambos lados de la casilla para poder colocar 2 fichas en la misma casilla.
    {{1, box_type::normal, color::none}, {Vector2i(746, 310), Vector2i(746, 325), Vector2i(746, 290)}},
    {{2, box_type::normal, color::none}, {Vector2i(708, 310), Vector2i(708, 325), Vector2i(708, 290)}},
    {{3, box_type::normal, color::none}, {Vector2i(670, 310), Vector2i(670, 325), Vector2i(670, 290)}},
    {{4, box_type::normal, color::none}, {Vector2i(632, 310), Vector2i(632, 325), Vector2i(632, 290)}},
    {{5, box_type::normal, color::none}, {Vector2i(594, 310), Vector2i(594, 325), Vector2i(594, 290)}},
    {{6, box_type::normal, color::none}, {Vector2i(556, 310), Vector2i(556, 325), Vector2i(556, 290)}},
    {{7, box_type::normal, color::none}, {Vector2i(518, 310), Vector2i(518, 325), Vector2i(518, 290)}},
    {{8, box_type::normal, color::none}, {Vector2i(482, 310), Vector2i(482, 325), Vector2i(482, 290)}},
    {{9, box_type::normal, color::none}, {Vector2i(462, 289), Vector2i(443, 289), Vector2i(477, 289)}},
    {{10, box_type::normal, color::none}, {Vector2i(462, 253), Vector2i(443, 253), Vector2i(477, 253)}},
    {{11, box_type::normal, color::none}, {Vector2i(462, 215), Vector2i(443, 215), Vector2i(477, 215)}},
    {{12, box_type::normal, color::none}, {Vector2i(462, 177), Vector2i(443, 177), Vector2i(477, 177)}},
    {{13, box_type::normal, color::none}, {Vector2i(462, 139), Vector2i(443, 139), Vector2i(477, 139)}},
    {{14, box_type::normal, color::none}, {Vector2i(462, 100), Vector2i(443, 100), Vector2i(477, 100)}},
    {{15, box_type::normal, color::none}, {Vector2i(462, 63), Vector2i(443, 63), Vector2i(477, 63)}},
    {{16, box_type::normal, color::none}, {Vector2i(462, 25), Vector2i(443, 25), Vector2i(477, 25)}},
    {{17, box_type::normal, color::none}, {Vector2i(384, 25), Vector2i(403, 25), Vector2i(366, 25)}},
    {{18, box_type::normal, color::none}, {Vector2i(310, 25), Vector2i(328, 25), Vector2i(394, 25)}},
    {{19, box_type::normal, color::none}, {Vector2i(310, 63), Vector2i(328, 63), Vector2i(394, 63)}},
    {{20, box_type::normal, color::none}, {Vector2i(310, 100), Vector2i(328, 100), Vector2i(394, 100)}},
    {{21, box_type::normal, color::none}, {Vector2i(310, 139), Vector2i(328, 139), Vector2i(394, 139)}},
    {{22, box_type::normal, color::none}, {Vector2i(310, 177), Vector2i(328, 177), Vector2i(394, 177)}},
    {{23, box_type::normal, color::none}, {Vector2i(310, 215), Vector2i(328, 215), Vector2i(394, 215)}},
    {{24, box_type::normal, color::none}, {Vector2i(310, 253), Vector2i(328, 253), Vector2i(394, 253)}},
    {{25, box_type::normal, color::none}, {Vector2i(310, 289), Vector2i(328, 289), Vector2i(394, 289)}},
    {{26, box_type::normal, color::none}, {Vector2i(288, 310), Vector2i(288, 325), Vector2i(288, 290)}},
    {{27, box_type::normal, color::none}, {Vector2i(253, 310), Vector2i(253, 325), Vector2i(253, 290)}},
    {{28, box_type::normal, color::none}, {Vector2i(216, 310), Vector2i(216, 325), Vector2i(216, 290)}},
    {{29, box_type::normal, color::none}, {Vector2i(178, 310), Vector2i(178, 325), Vector2i(178, 290)}},
    {{30, box_type::normal, color::none}, {Vector2i(139, 310), Vector2i(139, 325), Vector2i(139, 290)}},
    {{31, box_type::normal, color::none}, {Vector2i(101, 310), Vector2i(101, 325), Vector2i(101, 290)}},
    {{32, box_type::normal, color::none}, {Vector2i(64, 310), Vector2i(64, 325), Vector2i(64, 290)}},
    {{33, box_type::normal, color::none}, {Vector2i(25, 310), Vector2i(25, 325), Vector2i(25, 290)}},
    {{34, box_type::normal, color::none}, {Vector2i(25, 385), Vector2i(25, 366), Vector2i(25, 403)}},
    {{35, box_type::normal, color::none}, {Vector2i(25, 462), Vector2i(25, 444), Vector2i(25, 478)}},
    {{36, box_type::normal, color::none}, {Vector2i(64, 462), Vector2i(64, 444), Vector2i(64, 478)}},
    {{37, box_type::normal, color::none}, {Vector2i(101, 462), Vector2i(101, 444), Vector2i(101, 478)}},
    {{38, box_type::normal, color::none}, {Vector2i(139, 462), Vector2i(139, 444), Vector2i(139, 478)}},
    {{39, box_type::normal, color::none}, {Vector2i(178, 462), Vector2i(178, 444), Vector2i(178, 478)}},
    {{40, box_type::normal, color::none}, {Vector2i(216, 462), Vector2i(216, 444), Vector2i(216, 478)}},
    {{41, box_type::normal, color::none}, {Vector2i(253, 462), Vector2i(253, 444), Vector2i(253, 478)}},
    {{42, box_type::normal, color::none}, {Vector2i(288, 462), Vector2i(288, 444), Vector2i(288, 478)}},
    {{43, box_type::normal, color::none}, {Vector2i(310, 480), Vector2i(328, 555), Vector2i(394, 555)}},
    {{44, box_type::normal, color::none}, {Vector2i(310, 517), Vector2i(328, 517), Vector2i(394, 517)}},
    {{45, box_type::normal, color::none}, {Vector2i(310, 555), Vector2i(328, 555), Vector2i(394, 555)}},
    {{46, box_type::normal, color::none}, {Vector2i(310, 593), Vector2i(328, 593), Vector2i(394, 593)}},
    {{47, box_type::normal, color::none}, {Vector2i(310, 632), Vector2i(328, 632), Vector2i(394, 632)}},
    {{48, box_type::normal, color::none}, {Vector2i(310, 669), Vector2i(328, 669), Vector2i(394, 669)}},
    {{49, box_type::normal, color::none}, {Vector2i(310, 707), Vector2i(328, 707), Vector2i(394, 707)}},
    {{50, box_type::normal, color::none}, {Vector2i(310, 746), Vector2i(328, 746), Vector2i(394, 746)}},
    {{51, box_type::normal, color::none}, {Vector2i(384, 746), Vector2i(366, 746), Vector2i(403, 746)}},
    {{52, box_type::normal, color::none}, {Vector2i(462, 746), Vector2i(443, 746), Vector2i(477, 746)}},
    {{53, box_type::normal, color::none}, {Vector2i(462, 707), Vector2i(443, 707), Vector2i(477, 707)}},
    {{54, box_type::normal, color::none}, {Vector2i(462, 669), Vector2i(443, 669), Vector2i(477, 669)}},
    {{55, box_type::normal, color::none}, {Vector2i(462, 632), Vector2i(443, 632), Vector2i(477, 632)}},
    {{56, box_type::normal, color::none}, {Vector2i(462, 593), Vector2i(443, 593), Vector2i(477, 593)}},
    {{57, box_type::normal, color::none}, {Vector2i(462, 555), Vector2i(443, 555), Vector2i(477, 555)}},
    {{58, box_type::normal, color::none}, {Vector2i(462, 517), Vector2i(443, 517), Vector2i(477, 517)}},
    {{59, box_type::normal, color::none}, {Vector2i(462, 480), Vector2i(443, 480), Vector2i(477, 480)}},
    {{60, box_type::normal, color::none}, {Vector2i(482, 462), Vector2i(482, 444), Vector2i(482, 478)}},
    {{61, box_type::normal, color::none}, {Vector2i(518, 462), Vector2i(518, 444), Vector2i(518, 478)}},
    {{62, box_type::normal, color::none}, {Vector2i(556, 462), Vector2i(556, 444), Vector2i(556, 478)}},
    {{63, box_type::normal, color::none}, {Vector2i(594, 462), Vector2i(594, 444), Vector2i(594, 478)}},
    {{64, box_type::normal, color::none}, {Vector2i(632, 462), Vector2i(632, 444), Vector2i(632, 478)}},
    {{65, box_type::normal, color::none}, {Vector2i(670, 462), Vector2i(670, 444), Vector2i(670, 478)}},
    {{66, box_type::normal, color::none}, {Vector2i(708, 462), Vector2i(708, 444), Vector2i(708, 478)}},
    {{67, box_type::normal, color::none}, {Vector2i(746, 462), Vector2i(746, 444), Vector2i(746, 478)}},
    {{68, box_type::normal, color::none}, {Vector2i(746, 385), Vector2i(746, 366), Vector2i(746, 403)}},

    //Definición de los pasillos de colores hacia la meta
    //Para cada casilla definimos 3 posiciones: (1) En el centro de la casilla, (2) y (3) a ambos lados de la casilla para poder colocar 2 fichas en la misma casilla.
    //Pasillo rojo
    {{1, box_type::final_queue, color::red}, {Vector2i(63, 385), Vector2i(63, 366), Vector2i(63, 403)}},
    {{2, box_type::final_queue, color::red}, {Vector2i(101, 385), Vector2i(101, 366), Vector2i(101, 403)}},
    {{3, box_type::final_queue, color::red}, {Vector2i(139, 385), Vector2i(139, 366), Vector2i(139, 403)}},
    {{4, box_type::final_queue, color::red}, {Vector2i(177, 385), Vector2i(177, 366), Vector2i(177, 403)}},
    {{5, box_type::final_queue, color::red}, {Vector2i(215, 385), Vector2i(215, 366), Vector2i(215, 403)}},
    {{6, box_type::final_queue, color::red}, {Vector2i(253, 385), Vector2i(253, 366), Vector2i(253, 403)}},
    {{7, box_type::final_queue, color::red}, {Vector2i(291, 385), Vector2i(291, 366), Vector2i(291, 403)}},

    //Pasillo amarillo
    {{7, box_type::final_queue, color::yellow}, {Vector2i(480, 385), Vector2i(480, 366), Vector2i(480, 403)}},
    {{6, box_type::final_queue, color::yellow}, {Vector2i(518, 385), Vector2i(518, 366), Vector2i(518, 403)}},
    {{5, box_type::final_queue, color::yellow}, {Vector2i(556, 385), Vector2i(556, 366), Vector2i(556, 403)}},
    {{4, box_type::final_queue, color::yellow}, {Vector2i(594, 385), Vector2i(594, 366), Vector2i(594, 403)}},
    {{3, box_type::final_queue, color::yellow}, {Vector2i(632, 385), Vector2i(632, 366), Vector2i(632, 403)}},
    {{2, box_type::final_queue, color::yellow}, {Vector2i(670, 385), Vector2i(670, 366), Vector2i(670, 403)}},
    {{1, box_type::final_queue, color::yellow}, {Vector2i(708, 385), Vector2i(708, 366), Vector2i(708, 403)}},

    //Pasillo verde
    {{1, box_type::final_queue, color::green}, {Vector2i(384, 707), Vector2i(366, 707), Vector2i(403, 707)}},
    {{2, box_type::final_queue, color::green}, {Vector2i(384, 669), Vector2i(366, 669), Vector2i(403, 669)}},
    {{3, box_type::final_queue, color::green}, {Vector2i(384, 632), Vector2i(366, 632), Vector2i(403, 632)}},
    {{4, box_type::final_queue, color::green}, {Vector2i(384, 593), Vector2i(366, 593), Vector2i(403, 593)}},
    {{5, box_type::final_queue, color::green}, {Vector2i(384, 555), Vector2i(366, 555), Vector2i(403, 555)}},
    {{6, box_type::final_queue, color::green}, {Vector2i(384, 517), Vector2i(366, 517), Vector2i(403, 517)}},
    {{7, box_type::final_queue, color::green}, {Vector2i(384, 480), Vector2i(366, 480), Vector2i(403, 480)}},

    //Pasillo azul
    {{7, box_type::final_queue, color::blue}, {Vector2i(384, 289), Vector2i(366, 289), Vector2i(403, 289)}},
    {{6, box_type::final_queue, color::blue}, {Vector2i(384, 253), Vector2i(366, 253), Vector2i(403, 253)}},
    {{5, box_type::final_queue, color::blue}, {Vector2i(384, 215), Vector2i(366, 215), Vector2i(403, 215)}},
    {{4, box_type::final_queue, color::blue}, {Vector2i(384, 177), Vector2i(366, 177), Vector2i(403, 177)}},
    {{3, box_type::final_queue, color::blue}, {Vector2i(384, 139), Vector2i(366, 139), Vector2i(403, 139)}},
    {{2, box_type::final_queue, color::blue}, {Vector2i(384, 100), Vector2i(366, 100), Vector2i(403, 100)}},
    {{1, box_type::final_queue, color::blue}, {Vector2i(384, 63), Vector2i(366, 63), Vector2i(403, 63)}},

    //Casillas destino
    //Ponemos 4 posiciones, correspondientes a las 4 fichas
    //Verdes
    {{0, box_type::goal, color::green}, {Vector2i(384, 440), Vector2i(384, 408), Vector2i(415, 440), Vector2i(350, 440)}},
    //Azules
    {{0, box_type::goal, color::blue}, {Vector2i(384, 408), Vector2i(384, 354), Vector2i(415, 326), Vector2i(350, 326)}},
    //Rojas
    {{0, box_type::goal, color::red}, {Vector2i(329, 385), Vector2i(360, 385), Vector2i(329, 350), Vector2i(329, 420)}},
    //Amarillas
    {{0, box_type::goal, color::yellow}, {Vector2i(445, 385), Vector2i(412, 385), Vector2i(445, 350), Vector2i(445, 420)}},

    //Casillas home
    //Ponemos 4 posiciones, correspondientes a las 4 fichas
    //Verdes
    {{0, box_type::home, color::green}, {Vector2i(632, 594), Vector2i(594, 632), Vector2i(632, 670), Vector2i(670, 632)}},
    //Azules
    {{0, box_type::home, color::blue}, {Vector2i(139, 101), Vector2i(101, 139), Vector2i(139, 177), Vector2i(177, 139)}},
    //Rojas
    {{0, box_type::home, color::red}, {Vector2i(139, 594), Vector2i(101, 632), Vector2i(139, 670), Vector2i(177, 632)}},
    //Amarillas
    {{0, box_type::home, color::yellow}, {Vector2i(632, 101), Vector2i(594, 139), Vector2i(632, 139), Vector2i(670, 139)}},
    };

    public:
        inline ParchisGUI(){};
        void display();
        void moveFichas(float t, int i, box_type bt, color c, Sprite &);
        void moveFichas(float t, int i_orig, box_type bt_orig, color c_orig, int i_end, box_type bt_end, color c_end, Sprite &);
        void set_color(color my_color, Sprite &);
        void load_player(color my_color, Sprite & ficha1, Sprite & ficha2, Sprite & ficha3, Sprite & ficha4);
        int num_box(int pos_x, int pos_y);
};


#endif
