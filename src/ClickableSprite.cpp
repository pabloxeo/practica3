#include "ClickableSprite.h"

void ClickableSprite::setEnabled(bool b){
    this->enabled = b;
    onEnableAction();
}

void ClickableSprite::setSelected(bool b)
{
    this->enabled = b;
    onSelectionAction();
}

void ClickableSprite::setClicked(bool b)
{
    this->enabled = b;
    onClickAction();
}