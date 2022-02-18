#ifndef __CLICKABLESPRITE_H__
#define __CLICKABLESPRITE_H__

#include "IncludesSFML.h"

using namespace std;

class ClickableSprite: public Sprite{
    protected:
        bool enabled;
        bool selected;
        bool clicked;
        bool hovered;

    public:

        inline ClickableSprite(const Texture & t): Sprite(t) {};

        inline const bool isEnabled() const{return enabled;}

        inline const bool isSelected() const{return selected;}

        inline const bool isClicked() const{return clicked;}

        void setEnabled(bool b, Window & container);

        void setSelected(bool b, Window & container);
    
        void setClicked(bool b, Window & container);

        void setHovered(bool b, Window & container);

        virtual void onEnableAction(Window & container) = 0;

        virtual void onSelectionAction(Window & container) = 0;

        virtual void onClickAction(Window & container) = 0;

        virtual void onHoverAction(Window & container) = 0;

};

#endif