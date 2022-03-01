#include "DiceSprite.h"

const map<int, vector<int>> DiceSprite::num2textrec = {
    {1, {6, 118, 116, 116}},//{1, {2, 120, 120, 120}},
    {2, {122, 118, 116, 116}},//{2, {121, 120, 120, 120}},
    {3, {238, 118, 116, 116}},//{3, {237, 120, 120, 120}},
    {4, {353, 118, 116, 116}},//{4, {352, 120, 120, 120}},
    {5, {469, 118, 116, 116}},//{5, {468, 120, 120, 120}},
    {6, {584, 118, 116, 116}}//{6, {583, 120, 120, 120}}
};

const map<int, vector<int>> DiceSprite::num2selectedrec = {
    {1, {6, 236, 118, 118}},
    {2, {122, 236, 118, 118}},
    {3, {238, 236, 118, 118}},
    {4, {353, 236, 118, 118}},
    {5, {469, 236, 118, 118}},
    {6, {584, 236, 118, 118}}};

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

    if(!locked && enabled && clicked){
        gui->last_dice = this->number;
        gui->updateEnabledSprites();
    }
}

void DiceSprite::onEnableAction(Window & container) {}

void DiceSprite::onSelectionAction(Window & container) {}

void DiceSprite::onLockAction(Window & container) {}

void DiceSprite::onHoverAction(Window &container) {
    if (hovered)
    {
        if(locked || !enabled){
            ParchisGUI *gui = dynamic_cast<ParchisGUI *>(&container);
            gui->setForbiddenCursor();
        }
        else
            this->setTextureRect(IntRect(num2selectedrec.at(number).at(0), num2selectedrec.at(number).at(1), num2selectedrec.at(number).at(2), num2selectedrec.at(number).at(3)));
    }
    else
    {
        this->setTextureRect(IntRect(num2textrec.at(number).at(0), num2textrec.at(number).at(1), num2textrec.at(number).at(2), num2textrec.at(number).at(3)));
    }
}
