/* 
 * File:   SpriteNode.cpp
 * Author: dorian
 * 
 * Created on 13 de diciembre de 2014, 1:06
 */

#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture& texture): sprite(texture) {
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
                                                : sprite(texture, textureRect) {
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

SpriteNode::~SpriteNode() {
}

