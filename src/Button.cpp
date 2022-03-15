# include "Button.h"

Button::Button(const Texture & t):ClickableSprite(t){
    this->background_color = Color::White;
    this->click_action = NULL;
}

void Button::onClickAction(Window & container){
    this->click_action(container);
}

void Button::setClickAction(void (*action)(Window &)){
    this->click_action = action;
}

void Button::setText(String txt){

}

void Button::setTextColor(Color col){

}

void Button::setBackgroundColor(Color col){
    this->background_color = col;
    updateColor();
}

void Button::setButtonSize(Vector2f size){
    this->setButtonSize(size.x, size.y);
}

void Button::setButtonSize(float width, float height){
    float curr_width = this->getGlobalBounds().width;
    float curr_height = this->getGlobalBounds().height;
    this->setScale(width / curr_width, height / curr_height);
    this->text.setScale(width / curr_width, height / curr_height);
}

void Button::setButtonPosition(Vector2f pos){
    this->setButtonPosition(pos.x, pos.y);
}

void Button::setButtonPosition(float posx, float posy){
    this->setPosition(posx, posy);
    this->text.setPosition(posx, posy);
}