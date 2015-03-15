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
    Collision() : vertices() {};
    virtual ~Collision(){};

    void addVertice(sf::Vertex & vertex) {
        vertices.append(vertex);
    };
    
    sf::Rect<int> getAABB(){
        return sf::Rect<int>();
    };

private:
    sf::VertexArray vertices;

};

#endif	/* COLLISION_H */

