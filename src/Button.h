/* 
 * File:   Button.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 19:41
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "Component.h"
#include "ResourceHolder.h"
#include "IDFonts.h"
#include "IDTextures.h"
#include "Utilities.h"
#include "ButtonState.h"

#include <vector>
#include <wchar.h>
#include <memory>
#include <functional>
#include "Context.h"

namespace GUI {

    class Button : public Component {
    public:
        typedef std::function<void() > Callback;

        Button(Context context);
        virtual ~Button();

        void setCallback(Callback callback);
        void setText(const  wchar_t* text);
        void setToggle(bool flag);

        virtual bool isSelectable() const;
        virtual void select();
        virtual void deselect();
        virtual void activate();
        virtual void deactivate();
        virtual void handleEvent(const sf::Event& event);

    private:
        Callback callback;
        sf::Sprite sprite;
        sf::Text text;
        bool isToggle;
        SoundPlayer& mSounds;


        void changeTexture(ButtonState buttonType);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    };
}
#endif	/* BUTTON_H */

