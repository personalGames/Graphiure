/* 
 * File:   TileMapNode.cpp
 * Author: dorian
 * 
 * Created on 10 de febrero de 2015, 22:43
 */

#include "TileMapNode.h"
#include "StructMap.h"
#include <iostream>

TileMapNode::TileMapNode(const ResourceHolder<IDTextures, sf::Texture>& images,
        StructMap *mapInfo, int width, int height, 
        int numberRowsVisible, int numberColumnsVisible):

        numberRows(mapInfo->numberRows), numberColumns(mapInfo->numberColumns), 
        widthWindow(width),heightWindow(height), numberColumnsVisible(numberColumnsVisible), 
        numberRowsVisible(numberRowsVisible), tileset(images.get(IDTextures::TileSet))
        {
        
    tileSize=sf::Vector2u(mapInfo->tileWidth, mapInfo->tileHeight);
}

void TileMapNode::prepareMap(const int* tilesMap){
    //size in window
    sf::Vector2u quadSize = sf::Vector2u(widthWindow/numberColumnsVisible,
                                         heightWindow/(numberRowsVisible));
    // resize the vertex array to fit the level size (4 is for the four vertices))
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(widthWindow * heightWindow * 4);
    
    // populate the vertex array, with one quad per tile
    for (int i = 0; i < numberColumns; ++i) {
        for (int j = 0; j < numberRows; ++j) {
            // get the current tile number
            int tileNumber = tilesMap[i + j * numberColumns];

            // find its position in the tileset texture
            int division = (tileset.getSize().x / tileSize.x);
            int tu = tileNumber % division;
            int tv = tileNumber / division;

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &vertices[(i + j * numberColumns) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * quadSize.x, j * quadSize.y);
            quad[1].position = sf::Vector2f((i + 1) * quadSize.x, j * quadSize.y);
            quad[2].position = sf::Vector2f((i + 1) * quadSize.x, (j + 1) * quadSize.y);
            quad[3].position = sf::Vector2f(i * quadSize.x, (j + 1) * quadSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
}

void TileMapNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &tileset;

    // draw the vertex array
    target.draw(vertices, states);
}

TileMapNode::~TileMapNode() {

}
