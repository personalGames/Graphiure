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

/**
 * Nodo que representa la vida de una entidad
 */
class LifeNode : public SceneNode {
public:
    /**
     * 
     * @param texture imagenes
     * @param life la vida de la entidad
     * @param size el tamaño que se desea para el dibujado
     */
    LifeNode(ResourceHolder<std::string, sf::Texture>& texture, Life& life, sf::Vector2f size);
    virtual ~LifeNode();
    
private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    /**
     * La vida
     */
    Life* life;
    
    //AnimatedSprite heart;
    /**
     * FOndo de la barra de vida
     */
    AnimatedSprite background;
    /**
     * Relleno de la barra de vida
     */
    AnimatedSprite fill;
};

#endif	/* LIFENODE_H */

