#include "DiceSprite.h"

DiceSprite::DiceSprite(const Texture & t, int n, color c) : Sprite(t){
    this->enabled = true;
    this->number = n;
    this-> c = c;
    this->setTextureRect(IntRect(num2textrec[n][0], num2textrec[n][1], num2textrec[n][2], num2textrec[n][3]));
    this->setColor(color2Color[c]);
    this->setScale(Vector2f(0.5,0.5));
}