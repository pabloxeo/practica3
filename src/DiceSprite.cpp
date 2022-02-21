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
    if(clicked == true){
        gui->model->movePiece(this->getModelColor(), 0, this->getNumber());
        vector<tuple<color, int, Box>> last_moves = gui->model->getLastMoves();
        for (int i = 0; i < last_moves.size(); i++)
        {
            int idx = 0;
            bool collision = false;
            for (int k=0; k<none; k++){ //Para cada color...
                for (int j = 0; (!collision) && (j < gui->model->getBoard().getPieces((color)k).size()) ; j++){ //Para cada ficha del color si no hay colisión...
                    //Si ya hay una ficha en el centro del box...
                    if ((gui->pieces[(color)k][j].getPosition().x == gui->box2position.at(get<2>(last_moves[i]))[0].x) &&
                        (gui->pieces[(color)k][j].getPosition().y == gui->box2position.at(get<2>(last_moves[i]))[0].y)){
                            collision = true;
                             //La ficha actual se va al lado 1 del box...
                            idx = 1;
                            //Nuevo movimiento con la ficha con la que colisiona para que se vaya al lado 2 del box...
                            Sprite *animate_sprite2 = &gui->pieces[(color)k][j];
                            Vector2f animate_pos2 = Vector2f(gui->box2position.at(get<2>(last_moves[i]))[2].x, gui->box2position.at(get<2>(last_moves[i]))[2].y);
                            SpriteAnimator animator2 = SpriteAnimator(*animate_sprite2, animate_pos2, 1000);
                            gui->animations.push_back(animator2);
                    }
                    //Si ya hay una ficha en el lado 1 del box...
                    else if ((gui->pieces[(color)k][j].getPosition().x == gui->box2position.at(get<2>(last_moves[i]))[1].x) &&
                             (gui->pieces[(color)k][j].getPosition().y == gui->box2position.at(get<2>(last_moves[i]))[1].y)){
                            idx = 2; //Me nuevo al lado 2 del box
                    }
                    //Si ya hay una ficha en el lado 2 del box...
                    else if ((gui->pieces[(color)k][j].getPosition().x == gui->box2position.at(get<2>(last_moves[i]))[2].x) &&
                             (gui->pieces[(color)k][j].getPosition().y == gui->box2position.at(get<2>(last_moves[i]))[2].y)){
                            idx = 1; //Me nuevo al lado 1 del box
                    }
                }
            }
            Sprite *animate_sprite = &gui->pieces[get<0>(last_moves[i])][get<1>(last_moves[i])];
            Vector2f animate_pos = Vector2f(gui->box2position.at(get<2>(last_moves[i]))[idx].x, gui->box2position.at(get<2>(last_moves[i]))[idx].y);
            SpriteAnimator animator = SpriteAnimator(*animate_sprite, animate_pos, 1000);
            gui->animations.push_back(animator);
        }
    }
}

void DiceSprite::onEnableAction(Window & container) {}

void DiceSprite::onSelectionAction(Window & container) {}

void DiceSprite::onHoverAction(Window &container) {
    if (hovered)
    {
        this->setTextureRect(IntRect(num2selectedrec.at(number).at(0), num2selectedrec.at(number).at(1), num2selectedrec.at(number).at(2), num2selectedrec.at(number).at(3)));
    }
    else
    {
        this->setTextureRect(IntRect(num2textrec.at(number).at(0), num2textrec.at(number).at(1), num2textrec.at(number).at(2), num2textrec.at(number).at(3)));
    }
}
