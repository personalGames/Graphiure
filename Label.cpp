/* 
 * File:   Label.cpp
 * Author: dorian
 * 
 * Created on 13 de diciembre de 2014, 19:42
 */

#include "Label.h"

namespace GUI {

    Label::Label(const wchar_t* text, const ResourceHolder<IDFonts, sf::Font>& fonts)
    : text() {
        this->text.setString(text);
        this->text.setCharacterSize(16);
        this->text.setFont(fonts.get(IDFonts::Main));
    }

    bool Label::isSelectable() const {
        return false;
    }

    void Label::handleEvent(const sf::Event&) {
    }

    void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(text, states);
    }

    void Label::setText(const wchar_t* text) {
        this->text.setString(text);
    }
        Label::~Label() {

    }


}