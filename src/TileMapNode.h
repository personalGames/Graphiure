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
#include "StructMap.h"

class TileMapNode : public SceneNode {
public:
    TileMapNode(const ResourceHolder<std::string, sf::Texture>& images,
        StructMap *mapInfo, int  width, int heiht,
            int numberRowsVisible, int numberColumnsVisible);

    virtual ~TileMapNode();
    /**
     * Prepare the map after initialize the node with details like
     * numbers of rows/columns, size of windows...
     * @param tilesMap
     */
    void prepareMap(const int* tilesMap);
    
    inline sf::Vector2f getAdjustRatio(){
        return adjustedRatio;
    }
    
    sf::Vector2f getSizeMap();
    inline sf::Vector2f getQuadSize(){
        return quadSize;
    }

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:  
    sf::Vector2u tileSize;
    
    int numberRows;
    int numberColumns;
    
    int widthWindow;
    int heightWindow;
    
    int numberColumnsVisible;
    int numberRowsVisible;
    
    sf::Texture tileset;
    std::vector< std::vector <sf::VertexArray> > chunks;
    sf::Vector2f quadSize;
    sf::Vector2f adjustedRatio;

};

#endif	/* TILEMAPNODE_H */

