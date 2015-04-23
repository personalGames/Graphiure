/* 
 * File:   Collision.h
 * Author: dorian
 *
 * Created on 15 de marzo de 2015, 21:20
 */

#ifndef COLLISION_H
#define	COLLISION_H

#include <SFML/Graphics.hpp>

#include "TypeCollision.h"


class Collision {
public:
    Collision();
    virtual ~Collision();

    void addVertice(sf::Vertex & vertex);
    void addArrayVertex(sf::VertexArray& array);
    void setArrayVertex(sf::VertexArray* array);
    
    void update(sf::Transformable& transform);
    void applyRatio(sf::Vector2f ratio);
    inline sf::Transformable getTransform() {
        return transform;
    }
    
    TypeCollision getType() const {
        return type;
    }

    void setType(TypeCollision type) {
        this->type = type;
    }
    
    sf::FloatRect getAABB();
    sf::FloatRect getAABB(float time);
    sf::FloatRect getPreviousAABB();
    sf::FloatRect getAABBSwept();
    

    sf::VertexArray* vertices;
private:
    TypeCollision type;
    
    sf::Transformable transform;
    sf::Transformable previousTransform;
    
};

#endif	/* COLLISION_H */

