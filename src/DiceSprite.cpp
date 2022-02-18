#include "DiceSprite.h"

const map<int, vector<int>> DiceSprite::num2textrec = {
    {1, {2, 120, 120, 120}},
    {2, {121, 120, 120, 120}},
    {3, {237, 120, 120, 120}},
    {4, {352, 120, 120, 120}},
    {5, {468, 120, 120, 120}},
    {6, {583, 120, 120, 120}}
};

const map<color, Color> DiceSprite::color2Color = {
    {red, Color(204, 102, 102)},
    {blue, Color(102, 102, 204)},
    {green, Color(102, 204, 102)},
    {yellow, Color(255, 255, 127)},
    {none, Color::White}
};

DiceSprite::DiceSprite(const Texture & t, int n, color c) : ClickableSprite(t){
    this->enabled = true;
    this->number = n;
    this-> c = c;
    this->setTextureRect(IntRect(num2textrec.at(n).at(0), num2textrec.at(n).at(1), num2textrec.at(n).at(2), num2textrec.at(n).at(3)));
    this->setColor(color2Color.at(c));
    this->setScale(Vector2f(0.5,0.5));
}

void DiceSprite::onClickAction(Window & container) {
    ParchisGUI * gui = dynamic_cast<ParchisGUI*>(&container);
    if(clicked == true){
        gui->model->movePiece(this->getModelColor(), 0, this->getNumber());
        vector<tuple<color, int, Box>> last_moves = gui->model->getLastMoves();
        for (int i = 0; i < last_moves.size(); i++)
        {
            Sprite *animate_sprite = &gui->pieces[get<0>(last_moves[i])][get<1>(last_moves[i])];
            Vector2f animate_pos = Vector2f(gui->box2position.at(get<2>(last_moves[i]))[0].x, gui->box2position.at(get<2>(last_moves[i]))[0].y);
            SpriteAnimator animator = SpriteAnimator(*animate_sprite, animate_pos, 1000);
            gui->animations.push_back(animator);
        }
    }
}

void DiceSprite::onEnableAction(Window & container) {}

void DiceSprite::onSelectionAction(Window & container) {}

void DiceSprite::onHoverAction(Window &container) {}