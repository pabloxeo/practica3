# include "PieceSprite.h"

const map<color, vector<int>> PieceSprite::col2textrec = {
    {red, {30, 30, 30, 30}},
    {blue, {0, 30, 30, 30}},
    {green, {30, 0, 30, 30}},
    {yellow, {0, 0, 30, 30}}
};


PieceSprite::PieceSprite(const Texture & t, int id, color c) : ClickableSprite(t){
    this->enabled = true;
    this->id = id;
    this->c = c;
    this->setTextureRect(IntRect(col2textrec.at(c).at(0), col2textrec.at(c).at(1), col2textrec.at(c).at(2), col2textrec.at(c).at(3)));
}

void PieceSprite::onClickAction(){}

void PieceSprite::onEnableAction() {}

void PieceSprite::onSelectionAction() {}