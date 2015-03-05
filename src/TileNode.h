/* 
 * File:   TileMapNode.h
 * Author: dorian
 *
 * Created on 10 de febrero de 2015, 22:43
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
        StructMap *mapInfo, int  width, int heiht,
            int numberRowsVisible, int numberColumnsVisible);

    virtual ~TileNode();
    
    /**
     * Prepare the map after initialize the node with details like
     * numbers of rows/columns, size of windows...
     * @param tilesMap
     */
    void prepareMap(const std::vector< sf::Vector3i >& tilesMap);
    
    sf::Vector2f getSizeMap();
    inline sf::Vector2f getQuadSize(){
        return quadSize;
    }

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:  
    struct Tile{
        int x,y;
        sf::VertexArray vertices;
        
        Tile(int x, int y, sf::VertexArray& vertices):
                x(x),y(y),vertices(vertices){}
        
        Tile(const Tile &tile):
                x(tile.x),y(tile.y),vertices(tile.vertices){}
    };
    
    sf::Vector2u tileSize;
    
    int numberRows;
    int numberColumns;
    
    int widthWindow;
    int heightWindow;
    
    int numberColumnsVisible;
    int numberRowsVisible;
    
    sf::Texture tileset;
    std::vector< std::vector <Tile> > chunks;
    sf::Vector2f quadSize;
    
    

};

#endif	/* TILENODE_H */

