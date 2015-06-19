/* 
 * File:   Button.cpp
 * Author: dorian
 * 
 * Created on 13 de diciembre de 2014, 19:41
 */

#include "Button.h"

namespace GUI {

    Button::Button(Context context) : callback(),
    sprite(context.textures->get("Buttons.png")),
    text(), isToggle(false), mSounds(*context.sounds) {

        changeTexture(Normal);
        text.setCharacterSize(16);
        text.setString("");
        text.setFont(context.fonts->get(IDFonts::Main));

        sf::FloatRect bounds = sprite.getLocalBounds();
        text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
    }

    void Button::setCallback(Callback callback) {
        this->callback = std::move(callback);

    }

    void Button::setText(const wchar_t* text) {
        this->text.setString(text);
        centerOrigin(this->text);
    }

    void Button::setToggle(bool flag) {
        isToggle = flag;
    }

    bool Button::isSelectable() const {
        return true;
    }

    void Button::select() {
        Component::select();

        changeTexture(Selected);
    }

    void Button::deselect() {
        Component::deselect();

        changeTexture(Normal);
    }

    void Button::activate() {
        Component::activate();
        // If we are toggle then we should show that the button is pressed and thus "toggled".
        if (isToggle)
            changeTexture(Pressed);


        if (callback) {
            callback();
        }

        // If we are not a toggle then deactivate the button since we are just momentarily activated.
        if (!isToggle)
            deactivate();
        
        mSounds.play(SoundEffectID::Button);
    }

    void Button::deactivate() {
        Component::deactivate();

        if (isToggle) {
            // Reset texture to right one depending on if we are selected or not.
            if (isSelected())
                changeTexture(Selected);
            else
                changeTexture(Normal);
        }
    }

    void Button::handleEvent(const sf::Event&) {
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(sprite, states);
        target.draw(text, states);
    }

    void Button::changeTexture(ButtonState buttonType) {
        sf::IntRect textureRect(0, 50 * buttonType, 200, 50);
        sprite.setTextureRect(textureRect);
    }

    Button::~Button() {

    }
}
