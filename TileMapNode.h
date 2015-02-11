/* 
 * File:   TileMapNode.h
 * Author: dorian
 *
 * Created on 10 de febrero de 2015, 22:43
 */

#ifndef TILEMAPNODE_H
#define	TILEMAPNODE_H

#include "SceneNode.h"
#include "ResourceHolder.h"
#include <SFML/Graphics.hpp>
#include "IDTextures.h"

class TileMapNode : public SceneNode {
public:
    TileMapNode(const ResourceHolder<IDTextures, sf::Texture>& images,
        int numberRows, int numberColumns, int width, int heiht,
            int numberRowsVisible, int numberColumnsVisible);

    virtual ~TileMapNode();
    
    /**
     * Prepare the map after initialize the node with details like
     * numbers of rows/columns, size of windows...
     * @param tilesMap
     */
    void prepareMap(const int* tilesMap);

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::VertexArray vertices;
    sf::Texture tileset;
    
    int numberRows;
    int numberColumns;
    
    int widthWindow;
    int heightWindow;
    
    int numberRowsVisible;
    int numberColumnsVisible;

};

#endif	/* TILEMAPNODE_H */

