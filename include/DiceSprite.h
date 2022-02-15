#ifndef __DICESPRITE_H__
#define __DICESPRITE_H__

#include "IncludesSFML.h"
#include "Attributes.h"

using namespace std;

class DiceSprite: public Sprite{
    private:
        bool enabled;
        int number;
        color c;

        //Definiciones para los dados
        map <int, vector<int>> num2textrec = {
            {1, {2,120,120,120}},
            {2, {121,120,120,120}},
            {3, {237,120,120,120}},
            {4, {352,120,120,120}},
            {5, {468,120,120,120}},
            {6, {583,120,120,120}}
        };

        map <color, Color> color2Color = {
            {red, Color(204,102,102)},
            {blue, Color(102,102,204)},
            {green, Color(102,204,102)},
            {yellow, Color(255,255,127)},
            {none, Color::White}
        };

    public:
        DiceSprite(const Texture & t, int n, color c);

        inline int getNumber(){return number;}
        inline color getModelColor(){return this->c;}
};

#endif