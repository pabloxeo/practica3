#ifndef __PARCHISGUI_H__
#define __PARCHISGUI_H__

# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include <iostream>
# include <math.h>
# include <fstream>

using namespace sf;
using namespace std;

//Lista con los diferentes tipos de casillas
enum box_type {normal, home, final_queue, goal};

//Lista con los diferentes tipos de casillas
enum color {blue, red, green, yellow, none};

//Struct para definir las fichas: número de casilla y tipo
struct Piece
{
    int num;
    box_type type; 
    color col;
};

bool operator <(const Piece & a, const Piece & b){
    return a.num > b.num; 
}

class ParchisGUI{
    private: 
    map<Piece, vector<Vector2i>> box2position{
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
    {{17, box_type::normal, color::none}, {Vector2i(386, 25), Vector2i(403, 25), Vector2i(366, 25)}},
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
    {{34, box_type::normal, color::none}, {Vector2i(25, 383), Vector2i(25, 366), Vector2i(25, 403)}},
    {{35, box_type::normal, color::none}, {Vector2i(25, 462), Vector2i(25, 444), Vector2i(25, 478)}},
    {{36, box_type::normal, color::none}, {Vector2i(64, 462), Vector2i(64, 444), Vector2i(64, 478)}},
    {{37, box_type::normal, color::none}, {Vector2i(101, 462), Vector2i(101, 444), Vector2i(101, 478)}},
    {{38, box_type::normal, color::none}, {Vector2i(139, 462), Vector2i(139, 444), Vector2i(139, 478)}},
    {{39, box_type::normal, color::none}, {Vector2i(178, 462), Vector2i(178, 444), Vector2i(178, 478)}},
    {{40, box_type::normal, color::none}, {Vector2i(216, 462), Vector2i(216, 444), Vector2i(216, 478)}},
    {{41, box_type::normal, color::none}, {Vector2i(253, 462), Vector2i(253, 444), Vector2i(253, 478)}},
    {{42, box_type::normal, color::none}, {Vector2i(288, 462), Vector2i(288, 444), Vector2i(288, 478)}},
    {{43, box_type::normal, color::none}, {Vector2i(310, 555), Vector2i(328, 555), Vector2i(394, 555)}},
    {{44, box_type::normal, color::none}, {Vector2i(310, 517), Vector2i(328, 517), Vector2i(394, 517)}},
    {{45, box_type::normal, color::none}, {Vector2i(310, 555), Vector2i(328, 555), Vector2i(394, 555)}},
    {{46, box_type::normal, color::none}, {Vector2i(310, 593), Vector2i(328, 593), Vector2i(394, 593)}},
    {{47, box_type::normal, color::none}, {Vector2i(310, 632), Vector2i(328, 632), Vector2i(394, 632)}},
    {{48, box_type::normal, color::none}, {Vector2i(310, 669), Vector2i(328, 669), Vector2i(394, 669)}},
    {{49, box_type::normal, color::none}, {Vector2i(310, 707), Vector2i(328, 707), Vector2i(394, 707)}},
    {{50, box_type::normal, color::none}, {Vector2i(310, 746), Vector2i(328, 746), Vector2i(394, 746)}},
    {{51, box_type::normal, color::none}, {Vector2i(386, 746), Vector2i(366, 746), Vector2i(403, 746)}},
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
    {{68, box_type::normal, color::none}, {Vector2i(746, 383), Vector2i(746, 366), Vector2i(746, 403)}},
    };
    
    public:
        ParchisGUI(){};
        void display();
        void moveFichas();
};


#endif