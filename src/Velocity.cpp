/* 
 * File:   Velocity.cpp
 * Author: dorian
 * 
 * Created on 27 de marzo de 2015, 19:13
 */

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Velocity.h"
#include "Position.h"

#include <iostream>

Velocity::Velocity(): velocity(sf::Vector2f(0,0)) {
}

Velocity::Velocity(const Velocity& orig) {
    velocity=orig.velocity;
    maxVelocity=orig.maxVelocity;
}

Velocity::~Velocity() {
}

void Velocity::reset() {
    velocity.x=0;
    velocity.y=0;
}


void Velocity::adaptVelocity() {
    // If moving diagonally, reduce velocity (to have always same velocity)
    if (velocity.x != 0.f && velocity.y != 0.f) {
        this->setVelocity(velocity / std::sqrt(2.f));

    }
}

void Velocity::incrementVelocity(float x, float y) {
    incrementVelocity(sf::Vector2f(x,y));
}

void Velocity::incrementVelocity(sf::Vector2f increment) {
    increment*=maxVelocity;
    velocity+=increment;
}


bool Velocity::isQuiet() {
    return (velocity.x == 0 && velocity.y == 0);

}

void Velocity::updateVelocity(sf::Time dt, Position& actualPosition) {
    sf::Vector2f update=velocity*dt.asSeconds();
    actualPosition.updatePosition(static_cast<int> (update.x), static_cast<int> (update.y));
//    actualPosition.move(static_cast<int> (update.x), static_cast<int> (update.y));
}