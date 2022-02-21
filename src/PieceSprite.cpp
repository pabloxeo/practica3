# include "PieceSprite.h"

const map<color, vector<int>> PieceSprite::col2textrec = {
    {red, {30, 30, 30, 30}},
    {blue, {0, 30, 30, 30}},
    {green, {30, 0, 30, 30}},
    {yellow, {0, 0, 30, 30}}
};

const map<color, vector<int>> PieceSprite::col2selectedrec = {
    {red, {30, 90, 30, 30}},
    {blue, {0, 90, 30, 30}},
    {green, {30, 60, 30, 30}},
    {yellow, {0, 60, 30, 30}}
};

PieceSprite::PieceSprite(const Texture & t, int id, color c) : ClickableSprite(t){
    this->id = id;
    this->c = c;
    this->setTextureRect(IntRect(col2textrec.at(c).at(0), col2textrec.at(c).at(1), col2textrec.at(c).at(2), col2textrec.at(c).at(3)));
}

void PieceSprite::onClickAction(Window & container){}

void PieceSprite::onEnableAction(Window & container){}

void PieceSprite::onSelectionAction(Window & container){}

void PieceSprite::onHoverAction(Window & container){
    if(hovered){
        this->setTextureRect(IntRect(col2selectedrec.at(c).at(0), col2selectedrec.at(c).at(1), col2selectedrec.at(c).at(2), col2selectedrec.at(c).at(3)));
    }
    else{
        this->setTextureRect(IntRect(col2textrec.at(c).at(0), col2textrec.at(c).at(1), col2textrec.at(c).at(2), col2textrec.at(c).at(3)));
    }
}