#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "ClickableSprite.h"
#include "IncludesSFML.h"

using namespace std;

class Button: public ClickableSprite{
    protected:
        Text text;
        Color background_color;

        void (*click_action)(Window & container, Button &b);
        void (*enable_action)(Window &container, Button &b);
        void (*selection_action)(Window &container, Button &b);
        void (*hover_action)(Window &container, Button &b);
        void (*lock_action)(Window &container, Button &b);

    public:
        inline Button(): ClickableSprite(){}
        Button(const Texture & t);

        void onClickAction(Window &container);
        void onEnableAction(Window &container);
        void onSelectionAction(Window &container);
        void onHoverAction(Window &container);
        void onLockAction(Window &container);

        void setClickAction(void (*action)(Window & container, Button & this_btn));
        void setEnableAction(void (*action)(Window &container, Button &this_btn));
        void setSelectionAction(void (*action)(Window &container, Button &this_btn));
        void setHoverAction(void (*action)(Window &container, Button &this_btn));
        void setLockAction(void (*action)(Window &container, Button &this_btn));

        void setText(const String & txt);
        void setTextColor(Color col);
        void setBackgroundColor(Color col);
        virtual void refreshButton() = 0;

        void setButtonSize(Vector2f size);
        void setButtonSize(float width, float height);

        void setButtonPosition(Vector2f pos);
        void setButtonPosition(float posx, float posy);

};

#endif