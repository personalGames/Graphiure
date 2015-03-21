/* 
 * File:   Collision.cpp
 * Author: dorian
 * 
 * Created on 15 de marzo de 2015, 21:20
 */

#include "Collision.h"
#include <iostream>
#include "ConvexHull.h"

Collision::Collision() : vertices(), convexHull() {
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

void Collision::update(sf::Transformable& transform) {
    this->transform.setPosition(transform.getPosition());
}

void Collision::applyRatio(sf::Vector2f ratio) {
    for (uint i = 0; i < vertices.getVertexCount(); ++i) {
        vertices[i].position.x = (vertices[i].position.x) * ratio.x;
        vertices[i].position.y = (vertices[i].position.y) * ratio.y;
    }
    //hallo su nueva posición dado el ratio con el que está el mapa
    sf::Vector2f position = transform.getPosition();
    position.x *= ratio.x;
    position.y *= ratio.y;
    transform.setPosition(position);
}

sf::FloatRect Collision::getAABB() {
    sf::FloatRect cuadro = vertices.getBounds();
    return transform.getTransform().transformRect(cuadro);
}

bool Collision::collision(Collision* other) {
    sf::FloatRect one = getAABB();
    sf::FloatRect another = other->getAABB();

    return one.intersects(another);
}
