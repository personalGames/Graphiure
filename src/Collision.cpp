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

int Collision::collision(Collision* other) {
    sf::FloatRect one = getAABBSwept();
    sf::FloatRect another = other->getAABBSwept();
    
    //collision with swept (CCD) check the first moment collide
    if(one.intersects(another)){
        //if collide, get the first and final time of collision which binary search
        return 1;
    }else{
        return 0;
    }
    
    //if collide, divide the vertex in triangles and see if collide one of them
    
    //if collide

    //return one.intersects(another) ? 1 : 0;
}

sf::Vector2f Collision::normalSeparation(Collision* other, sf::Vector2f move) {
    float x = 0;
    float y = 0;

    sf::FloatRect me = getAABB();
    sf::FloatRect otherRect = other->getAABBSwept();
    sf::FloatRect intersection = sf::FloatRect();
    me.intersects(otherRect, intersection);

    //collision at vertical axis (y)
    if (intersection.width > intersection.height) {
        //collision at top
        if (intersection.contains(otherRect.left, otherRect.top)
                ||intersection.contains(otherRect.left+otherRect.width, otherRect.top)) {
            y = intersection.height+0.5;

            //collision at bottom
        } else {
            y = -(intersection.height+0.5);
        }

        //collision at horizontal axis (x)
    }else if (intersection.width < intersection.height) {
        //collision at right
        if (intersection.contains(otherRect.left + otherRect.width - 0.1, otherRect.top + 0.1)
                || intersection.contains(otherRect.left + otherRect.width - 0.1, 
                                        otherRect.top+otherRect.height + 0.1)) {
            x = -(intersection.width+0.5);

            //collision at left
        } else {
            x = intersection.width+0.5;
        }

    }
//    else if(intersection.width==intersection.height){
//        
//        sf::Vector2f substract=move;
//        std::cout<<substract.x<<" "<<substract.y<<std::endl;
//        if(substract.x!=0){
//            x=intersection.width;
//            
//        }
//        
//        if(substract.y!=0){
//            y=intersection.height;
//            
//        }
//        std::cout<<"Igualados"<<std::endl;
//    }

    return sf::Vector2f(x, y);
}
