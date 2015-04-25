/* 
 * File:   Position.cpp
 * Author: dorian
 * 
 * Created on 29 de marzo de 2015, 11:53
 */

#include <SFML/Graphics/Transformable.hpp>

#include "Position.h"

Position::Position(): position(), previousPosition(), direction(CardinalPoints::NORTH) {

}

Position::Position(Position& other) {
    this->direction=other.direction;
    this->position=other.position;
    this->previousPosition=other.previousPosition;
}


Position::~Position() {

}


void Position::updatePosition(float x, float y) {
    previousPosition=position;
    position.move(x,y);
}

void Position::setPositionIncrement(float x, float y) {
    position.move(x,y);
}


sf::Vector2f Position::getMoveVector() {
    return position.getPosition()-previousPosition.getPosition();
}

CardinalPoints Position::getDirection() {
    sf::Vector2f moveVector=getMoveVector();
    CardinalPoints cardinal=this->direction;
    if(moveVector.y!=0){
        cardinal=(moveVector.y>0)? CardinalPoints::SOUTH:CardinalPoints::NORTH;
    }
    
    if(moveVector.x!=0){
        cardinal=(moveVector.x>0)? CardinalPoints::EAST:CardinalPoints::WEST;
    }
    
    direction=cardinal;
    return cardinal;
}
