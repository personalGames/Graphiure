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


class TileNode : public SceneNode {
public:
    TileNode(const ResourceHolder<IDTextures, sf::Texture>& images);

    virtual ~TileNode();

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::VertexArray vertices;
    sf::Texture tileset;
};

#endif	/* TILENODE_H */

