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
    TileNode(const ResourceHolder<IDTextures, sf::Texture>& images, 
        sf::Vector2i position, StructMap *mapInfo, int width, int height, 
        int numberRowsVisible, int numberColumnsVisible);

    virtual ~TileNode();

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    int numberColumnsVisible;
    int numberRowsVisible;
    
    sf::Vector2i position;
    sf::Vector2u tileSize;
    sf::Texture tileset;
    sf::VertexArray vertices;
    sf::Vector2u quadSize;
};

#endif	/* TILENODE_H */

