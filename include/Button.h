#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "ClickableSprite.h"
#include "IncludesSFML.h"

using namespace std;

class Button: protected ClickableSprite{
    protected:
        Text text;
        Color background_color;

        void (*click_action)(Window & container);

    public:

        Button(const Texture & t);

        virtual void onClickAction(Window &container);
        virtual void onEnableAction(Window &container) = 0;
        virtual void onSelectionAction(Window &container) = 0;
        virtual void onHoverAction(Window &container) = 0;
        virtual void onLockAction(Window &container) = 0;

        virtual void setClickAction(void (*action)(Window & container));

        void setText(String txt);
        void setTextColor(Color col);
        void setBackgroundColor(Color col);
        virtual void updateColor() = 0;

        void setButtonSize(Vector2f size);
        void setButtonSize(float width, float height);

        void setButtonPosition(Vector2f pos);
        void setButtonPosition(float posx, float posy);

};

#endif