#ifndef __DICESPRITE_H__
#define __DICESPRITE_H__

#include "ClickableSprite.h"
#include "IncludesSFML.h"
#include "Attributes.h"

using namespace std;

class DiceSprite: public ClickableSprite{
    private:
        bool enabled;
        int number;
        color c;

        //Definiciones para los dados
        static const map <int, vector<int>> num2textrec;

        static const map <color, Color> color2Color;

    public:
        DiceSprite(const Texture & t, int n, color c);

        inline int getNumber(){return number;}
        inline color getModelColor(){return this->c;}

        void onClickAction();
        void onEnableAction();
        void onSelectionAction();
};

#endif