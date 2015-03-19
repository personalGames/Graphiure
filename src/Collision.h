/* 
 * File:   Collision.h
 * Author: dorian
 *
 * Created on 15 de marzo de 2015, 21:20
 */

#ifndef COLLISION_H
#define	COLLISION_H

#include <SFML/Graphics.hpp>

class Collision {
public:
    Collision();
    virtual ~Collision();

    void addVertice(sf::Vertex & vertex);
    void addArrayVertex(sf::VertexArray array);
    sf::FloatRect getAABB();
    bool collision(Collision* other);
    void update(sf::Transformable transform);
    void applyRatio(sf::Vector2f ratio);
    inline sf::Transformable getTransform() const {
        return transform;
    }
    

private:
    sf::VertexArray vertices;
    sf::Transformable transform;

};

#endif	/* COLLISION_H */

