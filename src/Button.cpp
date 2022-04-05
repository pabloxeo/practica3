# include "Button.h"
# include "ParchisGUI.h"

const map<color, vector<int>> SkipTurnButton::col2textrec = {
    {yellow, {0, 0, 255, 255}},
    {green, {0, 256, 255, 255}},
    {blue, {256, 0, 255, 255}},
    {red, {256, 256, 255, 255}}
};

const map<color, vector<int>> SkipTurnButton::col2selectedrec = {
    {yellow, {0, 512, 255, 255}},
    {green, {0, 768, 255, 255}},
    {blue, {255, 512, 255, 255}},
    {red, {255, 768, 255, 255}}
};

SkipTurnButton::SkipTurnButton(const Texture & t, color c): ParchisButton(t){
    this->setTexture(t);
    this->setModelColor(c);
}

void SkipTurnButton::setModelColor(color c){
    this->c = c;
    if(hovered && enabled && !locked)
        this->setTextureRect(IntRect(col2selectedrec.at(c).at(0), col2selectedrec.at(c).at(1), col2selectedrec.at(c).at(2), col2selectedrec.at(c).at(3)));
    else
        this->setTextureRect(IntRect(col2textrec.at(c).at(0), col2textrec.at(c).at(1), col2textrec.at(c).at(2), col2textrec.at(c).at(3)));

    if(enabled)
        this->setColor(Color::White);
    else
        this->setColor(Color(128, 128, 128));

}

void SkipTurnButton::onClickAction(Window & container){
    ParchisGUI * gui = dynamic_cast<ParchisGUI*>(&container);

    if(enabled && !locked && clicked){
        /* TODO */
    }
}

void SkipTurnButton::onEnableAction(Window & container){
    setModelColor(c);
}

void SkipTurnButton::onHoverAction(Window & container){
    if (hovered)
    {
        ParchisGUI *gui = dynamic_cast<ParchisGUI *>(&container);
        if (locked || !enabled)
        {
            gui->setForbiddenCursor();
        }
        else
        {
            gui->setHandCursor();
        }
    }
    setModelColor(c);
}

void SkipTurnButton::onLockAction(Window & container){
    setModelColor(c);
}

void SkipTurnButton::onSelectionAction(Window & container){
    setModelColor(c);
}

/* ------------------------------- DEPRECATED --------------------------------- */
NOButton::NOButton(const Texture & t):ClickableSprite(t){
    this->background_color = Color::White;
    this->click_action = NULL;
}

void NOButton::onClickAction(Window & container){
    refreshButton();
    this->click_action(container, *this);
}

void NOButton::setClickAction(void (*action)(Window &, NOButton &)){
    this->click_action = action;
}

void NOButton::onEnableAction(Window &container)
{
    refreshButton();
    this->enable_action(container, *this);
}

void NOButton::setEnableAction(void (*action)(Window &, NOButton &))
{
    refreshButton();
    this->enable_action = action;
}

void NOButton::onSelectionAction(Window &container)
{
    refreshButton();
    this->selection_action(container, *this);
}

void NOButton::setSelectionAction(void (*action)(Window &, NOButton &))
{
    refreshButton();
    this->selection_action = action;
}

void NOButton::onHoverAction(Window &container)
{
    refreshButton();
    this->hover_action(container, *this);
}

void NOButton::setHoverAction(void (*action)(Window &, NOButton &))
{
    refreshButton();
    this->hover_action = action;
}

void NOButton::onLockAction(Window &container)
{
    refreshButton();
    this->lock_action(container, *this);
}

void NOButton::setLockAction(void (*action)(Window &, NOButton &))
{
    refreshButton();
    this->lock_action = action;
}

void NOButton::setText(const String & txt){

}

void NOButton::setTextColor(Color col){

}

void NOButton::setBackgroundColor(Color col){
    this->background_color = col;
    refreshButton();
}

void NOButton::setButtonSize(Vector2f size){
    this->setButtonSize(size.x, size.y);
}

void NOButton::setButtonSize(float width, float height){
    float curr_width = this->getGlobalBounds().width;
    float curr_height = this->getGlobalBounds().height;
    this->setScale(width / curr_width, height / curr_height);
    this->text.setScale(width / curr_width, height / curr_height);
}

void NOButton::setButtonPosition(Vector2f pos){
    this->setButtonPosition(pos.x, pos.y);
}

void NOButton::setButtonPosition(float posx, float posy){
    this->setPosition(posx, posy);
    this->text.setPosition(posx, posy);
}