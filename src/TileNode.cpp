/* 
 * File:   TileNode.cpp
 * Author: dorian
 * 
 * Created on 10 de febrero de 2015, 0:52
 */

#include "TileNode.h"

TileNode::TileNode(const sf::Texture& image, sf::Vector2i position, int tile,
        sf::Vector2i tileSize, sf::Vector2f quadSize) :
position(position), tileSize(tileSize), tileset(image),
vertices(sf::Quads), quadSize(quadSize) {

    // find its position in the tileset texture
            int division = (tileset.getSize().x / tileSize.x);
            int tu = tile % division;
            int tv = tile/ division;
            --tu; //adjust the index

    sf::Vertex ver = *(new sf::Vertex());
    ver.position = sf::Vector2f(position.x * quadSize.x, position.y * quadSize.y);
    ver.texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
    vertices.append(std::move(ver));

    ver.position = sf::Vector2f((position.x + 1) * quadSize.x, position.y * quadSize.y);
    ver.texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
    vertices.append(std::move(ver));

    ver.position = sf::Vector2f((position.x + 1) * quadSize.x, (position.y + 1) * quadSize.y);
    ver.texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
    vertices.append(std::move(ver));

    ver.position = sf::Vector2f(position.x * quadSize.x, (position.y + 1) * quadSize.y);
    ver.texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    vertices.append(std::move(ver));
}

void TileNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &tileset;

        int left = 0, right = 0, top = 0, bottom = 0;
        //get chunk indices into which top left and bottom right points of view fall:
        sf::Vector2f temp = target.getView().getCenter()-(target.getView().getSize() / 2.f); //get top left point of view
        left = static_cast<int> (temp.x / tileSize.x); //posición x de la vista
        top = static_cast<int> (temp.y / tileSize.x); //posición y de la vista
    
        temp += target.getView().getSize(); //get bottom right point of view
        right = 1 + static_cast<int> (temp.x / tileSize.x); //posicion x final de la vista
        bottom = 1 + static_cast<int> (temp.y / tileSize.x); //posicion y final de la vista
        
        bool inside=true;
        for(int i=0; i<4 && !inside; ++i){
            sf::Vertex ver(vertices[i]);
            inside=((ver.position.x>left) & (ver.position.x<right)
                    & (ver.position.y>top) & (ver.position.y<bottom));
        }
        
        if(inside){
            target.draw(vertices,states);
        }
}

TileNode::~TileNode() {

}
