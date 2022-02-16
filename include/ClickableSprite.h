#ifndef __CLICKABLESPRITE_H__
#define __CLICKABLESPRITE_H__

#include "IncludesSFML.h"

using namespace std;

class ClickableSprite: public Sprite{
    protected:
        bool enabled;
        bool selected;
        bool clicked;

    public:

        inline ClickableSprite(const Texture & t): Sprite(t) {};

        inline const bool isEnabled() const{return enabled;}

        inline const bool isSelected() const{return selected;}

        inline const bool isClicked() const{return clicked;}

        void setEnabled(bool b);

        void setSelected(bool b);
    
        void setClicked(bool b);

        virtual void onEnableAction() = 0;

        virtual void onSelectionAction() = 0;

        virtual void onClickAction() = 0;
};

#endif