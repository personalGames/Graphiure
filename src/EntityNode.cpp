/* 
 * File:   EntityNode.cpp
 * Author: dorian
 * 
 * Created on 4 de marzo de 2015, 12:22
 */


#include "EntityNode.h"
#include "AnimatedSprite.h"
#include "StateMachineAnimation.h"
#include "Velocity.h"

EntityNode::EntityNode(Entity* entity) : entity(entity) {
    sf::Transformable* trans = entity->Get<sf::Transformable*>("Position");
    setOrigin(trans->getOrigin());
    setPosition(trans->getPosition());
    setScale(trans->getScale());
}

EntityNode::~EntityNode() {
}

void EntityNode::updateCurrent(sf::Time delta) {
    Velocity* velocity = this->entity->Get<Velocity*>("Velocity");
    velocity->adaptVelocity();

    sf::Transformable* position = this->entity->Get<sf::Transformable*>("Position");
    velocity->updateVelocity(delta, *position);
    if (velocity->isQuiet()) {
        entity->Get<StateMachineAnimation*>("Drawable")->update(Actions::None);
    }
    setPosition(position->getPosition());

    this->entity->Get<StateMachineAnimation*>("Drawable")->update(delta);

}

void EntityNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    entity->Get<StateMachineAnimation*>("Drawable")->draw(target, states);
}