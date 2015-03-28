/* 
 * File:   LifeNode.h
 * Author: dorian
 *
 * Created on 28 de marzo de 2015, 20:25
 */

#ifndef LIFENODE_H
#define	LIFENODE_H

#include "Life.h"
#include "AnimatedSprite.h"
#include "SceneNode.h"
#include "IXMLParser.h"

class LifeNode : public SceneNode {
public:
    LifeNode(ResourceHolder<std::string, sf::Texture>& texture, Life& life, sf::Vector2f size);
    virtual ~LifeNode();
    
private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    Life* life;
    
    AnimatedSprite heart;
    AnimatedSprite background;
    AnimatedSprite fill;
};

#endif	/* LIFENODE_H */

