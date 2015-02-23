/* 
 * File:   TileMapNode.cpp
 * Author: dorian
 * 
 * Created on 10 de febrero de 2015, 22:43
 */

#include "TileNode.h"

TileNode::TileNode(const ResourceHolder<IDTextures, sf::Texture>& images,
        StructMap *mapInfo, int width, int height,
        int numberRowsVisible, int numberColumnsVisible) :

numberRows(mapInfo->numberRows), numberColumns(mapInfo->numberColumns),
widthWindow(width), heightWindow(height), numberColumnsVisible(numberColumnsVisible),
numberRowsVisible(numberRowsVisible), tileset(images.get(IDTextures::TileSet)), chunks(), quadSize() {

    tileSize = sf::Vector2u(mapInfo->tileWidth, mapInfo->tileHeight);

}

void TileNode::prepareMap(const std::vector< sf::Vector3i >& tilesMap) {
    //size in window
    quadSize = sf::Vector2f(widthWindow / numberColumnsVisible,
            heightWindow / numberRowsVisible);

    int row = -1;
    int column = 0;
    std::vector< Tile > rowVector;
    for (uint i = 0; i < tilesMap.size(); ++i) {
        //get the tile
        sf::Vector3i tile(tilesMap[i]);

        column = tile.x;
        if (row != tile.y) {
            row = tile.y;
            if (rowVector.size()>0) {
                chunks.push_back(std::move(rowVector));
            }
            rowVector =*( new std::vector< Tile >);
        }

        // get the current tile number
        int tileNumber = tile.z;


        // find its position in the tileset texture
        int division = (tileset.getSize().x / tileSize.x);
        int tu = tileNumber % division;
        int tv = tileNumber / division;
        --tu; //adjust the index

        //create the rectangle vertices
        sf::VertexArray* quad = new sf::VertexArray(sf::Quads);

        //create the four vertices
        sf::Vertex ver = *(new sf::Vertex());
        ver.position = sf::Vector2f(tile.x * quadSize.x, tile.y * quadSize.y);
        ver.texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
        quad->append(std::move(ver));

        ver.position = sf::Vector2f((tile.x + 1) * quadSize.x, tile.y * quadSize.y);
        ver.texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
        quad->append(std::move(ver));

        ver.position = sf::Vector2f((tile.x + 1) * quadSize.x, (tile.y + 1) * quadSize.y);
        ver.texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        quad->append(std::move(ver));

        ver.position = sf::Vector2f(tile.x * quadSize.x, (tile.y + 1) * quadSize.y);
        ver.texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        quad->append(std::move(ver));

        //create the tile
        Tile tilePrepared* = new Tile(row, column, *quad);

        //append the tile to the row
        rowVector->push_back(*tilePrepared);
    }

    if (rowVector.size()>0) {
        chunks.push_back(std::move(rowVector));
    }
}

sf::Vector2f TileNode::getSizeMap() {
    sf::Vector2f result(numberColumns * quadSize.x, numberRows * quadSize.y);
    return result;
}

void TileNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &tileset;


    int left = 0, right = 0, top = 0, bottom = 0;
    //get chunk indices into which top left and bottom right points of view fall:
    sf::Vector2f temp = target.getView().getCenter()-(target.getView().getSize() / 2.f); //get top left point of view
    left = static_cast<int> (temp.x / quadSize.x) - 0.5;
    top = static_cast<int> (temp.y / quadSize.y) - 0.5;

    temp += target.getView().getSize(); //get bottom right point of view
    right = 1 + static_cast<int> (temp.x / quadSize.x) + 0.5;
    bottom = 1 + static_cast<int> (temp.y / quadSize.y) + 0.5;
    //clamp these to fit into array bounds:
    left = std::max(0, std::min(left, numberColumns));
    top = std::max(0, std::min(top, numberRows));
    right = std::max(0, std::min(right, numberColumns));
    bottom = std::max(0, std::min(bottom, numberRows));


    bool stillRow = true;
    bool stillColumn = true;

    int i = 0;
    int j = 0;
    while (stillColumn) {
        while (stillRow) {
            if (chunks[i][j].x > right) {
                stillRow = false;
            } else if (chunks[i][j].y > bottom) {
                stillColumn = false;
            }else if(chunks[i][j].x>left && chunks[i][j].y>top){
                //dibujar
                target.draw(chunks[i][j], states);
            }
            ++j;
        }
        j = 0;

        ++i;
        stillRow = true;
    }
}

TileNode::~TileNode() {

}
