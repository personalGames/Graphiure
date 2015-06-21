/* 
 * File:   StructCollision.h
 * Author: dorian
 *
 * Created on 31 de marzo de 2015, 11:13
 */

#ifndef STRUCTCOLLISION_H
#define	STRUCTCOLLISION_H

#include <string>
#include <SFML/Graphics.hpp>

/**
 * Estructura para guardar información de colisiones
 */
struct StructCollision {
    StructCollision():vertices(), typeCollision(), position() {};
    virtual ~StructCollision(){};

    sf::VertexArray* vertices;
    std::string typeCollision;
    sf::Vector2f position;
    std::string* data;
};

#endif	/* STRUCTCOLLISION_H */

