# include "Button.h"

Button::Button(const Texture & t):ClickableSprite(t){
    this->background_color = Color::White;
    this->click_action = NULL;
}

void Button::onClickAction(Window & container){
    refreshButton();
    this->click_action(container, *this);
}

void Button::setClickAction(void (*action)(Window &, Button &)){
    this->click_action = action;
}

void Button::onEnableAction(Window &container)
{
    refreshButton();
    this->enable_action(container, *this);
}

void Button::setEnableAction(void (*action)(Window &, Button &))
{
    refreshButton();
    this->enable_action = action;
}

void Button::onSelectionAction(Window &container)
{
    refreshButton();
    this->selection_action(container, *this);
}

void Button::setSelectionAction(void (*action)(Window &, Button &))
{
    refreshButton();
    this->selection_action = action;
}

void Button::onHoverAction(Window &container)
{
    refreshButton();
    this->hover_action(container, *this);
}

void Button::setHoverAction(void (*action)(Window &, Button &))
{
    refreshButton();
    this->hover_action = action;
}

void Button::onLockAction(Window &container)
{
    refreshButton();
    this->lock_action(container, *this);
}

void Button::setLockAction(void (*action)(Window &, Button &))
{
    refreshButton();
    this->lock_action = action;
}

void Button::setText(const String & txt){

}

void Button::setTextColor(Color col){

}

void Button::setBackgroundColor(Color col){
    this->background_color = col;
    refreshButton();
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