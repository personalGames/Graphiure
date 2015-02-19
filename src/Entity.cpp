/* 
 * File:   Entity.cpp
 * Author: dorian
 * 
 * Created on 15 de febrero de 2015, 14:13
 */

#include "Entity.h"

Entity::Entity() : velocity() {
}

Entity::~Entity() {
}

void Entity::setVelocity(sf::Vector2f velocity) {
    this->velocity = velocity;
}

void Entity::setVelocity(float x, float y) {
    this->velocity.x = x;
    this->velocity.y = y;
}

void Entity::updateCurrent(sf::Time delta, CommandQueue&) {
    //move is a function of sfml. Adds to the current position by moving
    //an offset unlike setPosition which overwrites it.
    move(velocity * delta.asSeconds());
}

void Entity::accelerate(sf::Vector2f velocity) {
    this->velocity += velocity;
}

void Entity::accelerate(float vx, float vy) {
    velocity.x += vx;
    velocity.y += vy;
}
