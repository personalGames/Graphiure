/* 
 * File:   Collision.cpp
 * Author: dorian
 * 
 * Created on 15 de marzo de 2015, 21:20
 */

#include "Collision.h"
#include <iostream>

Collision::Collision() : vertices() {
}

Collision::~Collision() {
}

void Collision::addArrayVertex(sf::VertexArray array) {
    for (uint i = 0; i < array.getVertexCount(); ++i) {
        vertices.append(array[i]);
    }
}

void Collision::addVertice(sf::Vertex& vertex) {
    vertices.append(vertex);
}

void Collision::update(sf::Transformable transform) {
    this->transform = transform;
}

void Collision::applyRatio(sf::Vector2f ratio) {
//    transform.setScale(ratio);
//    std::cout<<transform.getPosition().x<<" "<<transform.getPosition().y<<std::endl;
//    for(uint i=0; i<vertices.getVertexCount(); ++i){
//        vertices[i].position.x=(vertices[i].position.x)*ratio.x;
//        vertices[i].position.y=(vertices[i].position.y)*ratio.y;
//    }
}


sf::FloatRect Collision::getAABB() {
    return transform.getTransform().transformRect(vertices.getBounds());
}

bool Collision::collision(Collision* other) {
    sf::FloatRect one = getAABB();
    sf::FloatRect another = other->getAABB();
    
    return one.intersects(another);
}
