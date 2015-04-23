/* 
 * File:   Collision.cpp
 * Author: dorian
 * 
 * Created on 15 de marzo de 2015, 21:20
 */

#include "Collision.h"
#include "ActionStack.h"
#include <iostream>

Collision::Collision() : type(TypeCollision::STATIC) {
    vertices = new sf::VertexArray();
}

Collision::~Collision() {
}

void Collision::addArrayVertex(sf::VertexArray& array) {
    for (uint i = 0; i < array.getVertexCount(); ++i) {
        vertices->append(array[i]);
    }
}

void Collision::setArrayVertex(sf::VertexArray* array) {
    //borro el anterior
    delete vertices;
    //y pongo el nuevo
    vertices = array;
}

void Collision::addVertice(sf::Vertex& vertex) {
    vertices->append(vertex);
}

void Collision::update(sf::Transformable& transform) {
    this->previousTransform.setPosition(this->transform.getPosition());
    this->transform.setPosition(transform.getPosition());
}

void Collision::applyRatio(sf::Vector2f ratio) {
    for (uint i = 0; i < vertices->getVertexCount(); ++i) {
        (*vertices)[i].position.x = ((*vertices)[i].position.x) * ratio.x;
        (*vertices)[i].position.y = ((*vertices)[i].position.y) * ratio.y;
    }
    //hallo su nueva posición dado el ratio con el que está el mapa
    sf::Vector2f position = transform.getPosition();
    position.x *= ratio.x;
    position.y *= ratio.y;
    transform.setPosition(position);
}

sf::FloatRect Collision::getAABB() {
    sf::FloatRect cuadro = vertices->getBounds();
    return transform.getTransform().transformRect(cuadro);
}

sf::FloatRect Collision::getAABB(float time) {
    sf::FloatRect cuadro = vertices->getBounds();
    sf::Vector2f update=(transform.getPosition()-previousTransform.getPosition())*time;
    sf::Transformable f=sf::Transformable();
    f.setPosition(previousTransform.getPosition());
    f.move(static_cast<int> (update.x), static_cast<int> (update.y));
    return f.getTransform().transformRect(cuadro);
}

sf::FloatRect Collision::getPreviousAABB(){
    sf::FloatRect cuadro = vertices->getBounds();
    return previousTransform.getTransform().transformRect(cuadro);
}

sf::FloatRect Collision::getAABBSwept() {
    sf::FloatRect AABBFinal=getAABB();
    sf::FloatRect AABBInitial=getPreviousAABB();
    if(AABBFinal==AABBInitial){
        return AABBFinal;
    }
    sf::FloatRect result=sf::FloatRect();
    result.left=std::min(AABBFinal.left, AABBInitial.left);
    result.top=std::min(AABBFinal.top, AABBInitial.top);
    float calculus= (std::max(AABBFinal.left+AABBFinal.width, AABBInitial.left+AABBInitial.width)) - result.left;
    result.width=calculus;
    calculus= (std::max(AABBFinal.top+AABBFinal.height, AABBInitial.top+AABBInitial.height)) - result.top;
    result.height=calculus;
    
    return result;
}
