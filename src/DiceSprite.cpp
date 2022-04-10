#include "DiceSprite.h"
#include "ParchisGUI.h"

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

const map<color, Color> DiceSprite::color2DisabledColor = {
    {red, Color(204 / 2, 102 / 2, 102 / 2)},
    {blue, Color(102 / 2, 102 / 2, 204 / 2)},
    {green, Color(102 / 2, 204 / 2, 102 / 2)},
    {yellow, Color(255 / 2, 255 / 2, 127 / 2)},
    {none, Color::White}
};

const map<color, Color> DiceSprite::color2SelectedColor = {
    {red, Color(255, 0, 0)},
    {blue, Color(0, 255, 255)},
    {green, Color(192, 255, 0)},
    {yellow, Color(255, 192, 0)},
    {none, Color::White}};

DiceSprite::DiceSprite(const Texture & t, int n, color c) : ClickableSprite(t){
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
        gui->updateSprites();
    }
}

void DiceSprite::onEnableAction(Window & container) {
    if(this->enabled){
        this->setColor(color2Color.at(c));
    }
    else{
        this->setColor(color2DisabledColor.at(c));
    }
}

void DiceSprite::onSelectionAction(Window & container){
    if(this->selected){
        this->setColor(color2SelectedColor.at(c));
    }
    else if(!this->enabled){
        this->setColor(color2DisabledColor.at(c));
    }
    else{
        this->setColor(color2Color.at(c));
    }
}

void DiceSprite::onLockAction(Window & container) {}

void DiceSprite::onHoverAction(Window &container) {
    if (hovered)
    {
        //cout << enabled << endl;
        //cout << ClickableSprite::enabled << endl;
        ParchisGUI *gui = dynamic_cast<ParchisGUI *>(&container);
        if(locked || !enabled){
            gui->setForbiddenCursor();
        }
        else{
            this->setTextureRect(IntRect(num2selectedrec.at(number).at(0), num2selectedrec.at(number).at(1), num2selectedrec.at(number).at(2), num2selectedrec.at(number).at(3)));
            gui->setHandCursor();
        }
    }
    else
    {
        this->setTextureRect(IntRect(num2textrec.at(number).at(0), num2textrec.at(number).at(1), num2textrec.at(number).at(2), num2textrec.at(number).at(3)));
    }
}
