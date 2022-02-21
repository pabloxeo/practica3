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

void PieceSprite::onClickAction(Window & container){

    ParchisGUI * gui = dynamic_cast<ParchisGUI*>(&container);

    if(clicked == true){
        gui->model->movePiece(this->getModelColor(), this->id,  gui->last_dice);
        vector<tuple<color, int, Box>> last_moves = gui->model->getLastMoves();
        for (int i = 0; i < last_moves.size(); i++)
        {
            int idx = 0;
            bool collision = false;
            for (int k=0; k<none; k++){ //Para cada color
                for (int j = 0; (!collision) && (j < gui->model->getBoard().getPieces((color)k).size()) ; j++){ //Para cada ficha del color si no hay colisión...
                    //Si ya hay una ficha en el centro del box
                    if ((gui->pieces[(color)k][j].getPosition().x == gui->box2position.at(get<2>(last_moves[i]))[0].x) &&
                        (gui->pieces[(color)k][j].getPosition().y == gui->box2position.at(get<2>(last_moves[i]))[0].y)){
                            collision = true;
                             //La ficha actual se va al lado 1 del box
                            idx = 1;
                            //Nuevo movimiento con la ficha con la que colisiona para que se vaya al lado 2 del box
                            Sprite *animate_sprite2 = &gui->pieces[(color)k][j];
                            Vector2f animate_pos2 = Vector2f(gui->box2position.at(get<2>(last_moves[i]))[2].x, gui->box2position.at(get<2>(last_moves[i]))[2].y);
                            SpriteAnimator animator2 = SpriteAnimator(*animate_sprite2, animate_pos2, 1000);
                            gui->animations.push_back(animator2);
                    }
                    //Si ya hay una ficha en el lado 1 del box
                    else if ((gui->pieces[(color)k][j].getPosition().x == gui->box2position.at(get<2>(last_moves[i]))[1].x) &&
                             (gui->pieces[(color)k][j].getPosition().y == gui->box2position.at(get<2>(last_moves[i]))[1].y)){
                            idx = 2; //Me nuevo al lado 2 del box
                    }
                    //Si ya hay una ficha en el lado 2 del box
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