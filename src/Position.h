/* 
 * File:   Position.h
 * Author: dorian
 *
 * Created on 29 de marzo de 2015, 11:53
 */

#ifndef POSITION_H
#define	POSITION_H

#include <SFML/Graphics.hpp>

#include "CardinalPoints.h"

class Position {
public:
    Position();
    Position(Position& other);
    virtual ~Position();

    /**
     * Normal update
     * @param x
     * @param y
     */
    void updatePosition(float x, float y);
    
    inline sf::Transformable getPosition() const {
        return position;
    }

    inline void setPosition(sf::Transformable position) {
        this->previousPosition=position;
        this->position = position;
    }
    
    inline void setPosition(float x, float y){
        previousPosition.setPosition(x,y);
        position.setPosition(x,y);
    }
    
    void setPositionIncrement(float x, float y);
   
    CardinalPoints getDirection();
    
private:
    sf::Transformable position;
    sf::Transformable previousPosition;
    
    CardinalPoints direction;
    
    sf::Vector2f getMoveVector();
};

#endif	/* POSITION_H */

