/* 
 * File:   EntityNode.cpp
 * Author: dorian
 * 
 * Created on 4 de marzo de 2015, 12:22
 */


#include "EntityNode.h"
#include "AnimatedSprite.h"

EntityNode::EntityNode(Entity2* entity): entity(entity) {
}

EntityNode::~EntityNode() {
}

void EntityNode::setVelocity(sf::Vector2f velocity) {
    this->entity->Set<sf::Vector2f>("Velocity",velocity);
    //this->velocity = velocity;
}

void EntityNode::setVelocity(float x, float y) {
    this->entity->Set<sf::Vector2f>("Velocity",sf::Vector2f(x,y));
    //this->velocity.x = x;
    //this->velocity.y = y;
}

void EntityNode::updateCurrent(sf::Time delta, CommandQueue&) {
    //move is a function of sfml. Adds to the current position by moving
    //an offset unlike setPosition which overwrites it.
    //sf::Vector2f s=velocity * delta.asSeconds();
    sf::Vector2f s=(this->entity->Get<sf::Vector2f>("Velocity"))
                        * delta.asSeconds();
    move(static_cast<int>(s.x), static_cast<int>(s.y));
}

void EntityNode::accelerate(sf::Vector2f velocity) {
    //this->velocity += velocity;
}

void EntityNode::accelerate(float vx, float vy) {
    //velocity.x += vx;
    //velocity.y += vy;
}

unsigned int EntityNode::getCategory() const {
    return Category::CHARACTER;
}
void EntityNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(entity->Get<AnimatedSprite>("Drawable"), states);
}
