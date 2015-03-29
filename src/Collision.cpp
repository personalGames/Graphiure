/* 
 * File:   Collision.cpp
 * Author: dorian
 * 
 * Created on 15 de marzo de 2015, 21:20
 */

#include "Collision.h"

Collision::Collision() : type(TypeCollision::STATIC), vertices() {
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

int Collision::collision(Collision* other) {
    sf::FloatRect one = getAABB();
    sf::FloatRect another = other->getAABB();

    return one.intersects(another)? 1:0;
}

sf::Vector2f Collision::normalSeparation(Collision* other){
    float x=0;
    float y=0;
    
    sf::FloatRect me=getAABB();
    sf::FloatRect otherRect=other->getAABB();
    sf::FloatRect intersection=sf::FloatRect();
    me.intersects(otherRect, intersection);
    
    //collision at vertical axis (y)
    if(intersection.width > intersection.height){
        //collision at top
        if(intersection.contains(intersection.left, otherRect.top)){
            y=intersection.height;
            
        //collision at bottom
        }else{
            y=-intersection.height;
        }
        
    //collision at horizontal axis (x)
    }else if(intersection.width<intersection.height){
        if(intersection.contains(otherRect.left+otherRect.width-1.f, otherRect.top+1.f)){
            x=-intersection.width;
        }else{
            x=intersection.width;
        }
    }
    
    
    // Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
//    if (area.width > area.height)
//    {
//        if (area.contains({ area.left, player.getPosition().y }))
//        {
//            // Up side crash
//            player.setPosition({ player.getPosition().x, player.getPosition().y + area.height });
//        }
//        else
//        {
//            // Down side crash
//            player.setPosition({ player.getPosition().x, player.getPosition().y - area.height });
//        }
//    }
//    else if (area.width < area.height)
//    {
//        if (area.contains({ player.getPosition().x + player.getGlobalBounds().width - 1.f, area.top + 1.f }))
//        {
//            //Right side crash
//            player.setPosition({ player.getPosition().x - area.width, player.getPosition().y });
//        }
//        else
//        {
//            //Left side crash
//            player.setPosition({ player.getPosition().x + area.width, player.getPosition().y });
//        }
//    } 
    
    return sf::Vector2f(x,y);
}
