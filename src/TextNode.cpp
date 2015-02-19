/* 
 * File:   TextNode.cpp
 * Author: dorian
 * 
 * Created on 14 de diciembre de 2014, 15:05
 */

#include "TextNode.h"

TextNode::TextNode(const ResourceHolder<IDFonts, sf::Font>& fonts, const std::string& text) {
    this->text.setFont(fonts.get(IDFonts::Main));
    this->text.setCharacterSize(20);
    setString(text);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(text, states);
}

void TextNode::setString(const std::string& text) {
    this->text.setString(text);
    centerOrigin(this->text);
}