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

sf::FloatRect Collision::getAABB() {
    return transform.getTransform().transformRect(vertices.getBounds());
}

bool Collision::collision(Collision* other) {
    sf::FloatRect one = getAABB();
    sf::FloatRect another = other->getAABB();

//    std::cout<<std::endl<<std::endl << "Compare x: " << one.top << std::endl;
//    std::cout << "Compare y: " << one.left << std::endl;
//    std::cout << "Compare height: " << another.height << std::endl;
//    std::cout << "Compare width: " << another.width << std::endl<<std::endl;
//    
//    std::cout << "Compare x: " << another.top << std::endl;
//    std::cout << "Compare y: " << another.left << std::endl;
//    std::cout << "Compare height: " << another.height << std::endl;
//    std::cout << "Compare widht: " << another.width << std::endl;
    
    return one.intersects(another);
}
