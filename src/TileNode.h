/* 
 * File:   TileNode.h
 * Author: dorian
 *
 * Created on 10 de febrero de 2015, 0:52
 */

#ifndef TILENODE_H
#define	TILENODE_H

#include "SceneNode.h"
#include "ResourceHolder.h"
#include <SFML/Graphics.hpp>
#include "IDTextures.h"
#include "StructMap.h"

class TileNode : public SceneNode {
public:
    TileNode(const sf::Texture& image, sf::Vector2i position, int tile,
        sf::Vector2i tileSize, sf::Vector2f quadSize);

    virtual ~TileNode();

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    
    sf::Vector2i position;
    sf::Vector2u tileSize;
    sf::Texture tileset;
    sf::VertexArray vertices;
    sf::Vector2f quadSize;
};

#endif	/* TILENODE_H */

