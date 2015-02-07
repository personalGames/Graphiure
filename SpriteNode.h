/* 
 * File:   SpriteNode.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 1:06
 */

#ifndef SPRITENODE_H
#define	SPRITENODE_H

#include "SceneNode.h"
#include <SFML/Graphics.hpp>

/**
 * A concrete SceneNode with a sprite to draw
 */
class SpriteNode : public SceneNode {
public:
    /**
     * 
     * @param texture of the sprite
     */
    SpriteNode(const sf::Texture& texture);
    /**
     * 
     * @param texture of the sprite
     * @param textureRect region of the texture to draw
     */
    SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);
    virtual ~SpriteNode();
    /**
     * Inherit from SceneNode, draw the sprite
     * @param target
     * @param states
     */
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    /**
     * The sprite of the node
     */
    sf::Sprite sprite;

};

#endif	/* SPRITENODE_H */

