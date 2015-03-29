/* 
 * File:   Position.cpp
 * Author: dorian
 * 
 * Created on 29 de marzo de 2015, 11:53
 */

#include <SFML/Graphics/Transformable.hpp>

#include "Position.h"

Position::Position(): position(), previousPosition() {

}

Position::~Position() {

}


void Position::updatePosition(float x, float y) {
    previousPosition=position;
    position.move(x,y);
}

sf::Vector2f Position::getMoveVector() {
    return position.getPosition()-previousPosition.getPosition();
}
