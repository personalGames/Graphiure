/* 
 * File:   TileNode.cpp
 * Author: dorian
 * 
 * Created on 10 de febrero de 2015, 0:52
 */

#include "TileNode.h"

TileNode::TileNode(const ResourceHolder<IDTextures, sf::Texture>& images, 
        sf::Vector2i position, StructMap *mapInfo, int width, int height, 
        int numberRowsVisible, int numberColumnsVisible) :
position(position), tileset(images.get(IDTextures::TileSet)), vertices(sf::Quads) {

    tileSize = sf::Vector2u(mapInfo->tileWidth, mapInfo->tileHeight);
    //size in window
    quadSize = sf::Vector2u(width / numberColumnsVisible,
            height / (numberRowsVisible));
}

void TileNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &tileset;

    int left = 0, right = 0, top = 0, bottom = 0;
    sf::Vector2i topLeft, bottomRight;
    //get chunk indices into which top left and bottom right points of view fall:
    sf::Vector2f temp = target.getView().getCenter()-(target.getView().getSize() / 2.f); //get top left point of view
    left = static_cast<int> (temp.x / tileSize.x); //posición x de la vista
    top = static_cast<int> (temp.y / tileSize.x); //posición y de la vista

    temp += target.getView().getSize(); //get bottom right point of view
    right = 1 + static_cast<int> (temp.x / tileSize.x); //posicion x final de la vista
    bottom = 1 + static_cast<int> (temp.y / tileSize.x); //posicion y final de la vista

    if (position.x>=left && position.y>=top
            && position.x <= right && position.y<=bottom) {
        target.draw(vertices, states);
    }
}

TileNode::~TileNode() {

}
