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
    sf::FloatRect getAABB(); //first level of collision, will add another two
    int collision(Collision* other);
    void update(sf::Transformable& transform);
    void applyRatio(sf::Vector2f ratio);
    sf::Vector2f normalSeparation(Collision* other);
    inline sf::Transformable* getTransform() {
        return &transform;
    }
    
    TypeCollision getType() const {
        return type;
    }

    void setType(TypeCollision type) {
        this->type = type;
    }
    

private:
    TypeCollision type;
    sf::VertexArray* vertices;
    sf::Transformable transform;
};

#endif	/* COLLISION_H */

