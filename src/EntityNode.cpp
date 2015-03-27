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
    //    velocity->reset();


    //    adaptVelocity();
    //    //animatedCharacter.update(dt); actualizar renderizado
    //    //eso tendría que ir en el sistema de renderizado
    //    //move is a function of sfml. Adds to the current position by moving
    //    //an offset unlike setPosition which overwrites it.
    //    //sf::Vector2f s=velocity * delta.asSeconds();
    //    sf::Vector2f s=(this->entity->Get<sf::Vector2f>("Velocity"))
    //                        * delta.asSeconds();
    //    move(static_cast<int>(s.x), static_cast<int>(s.y));
    //
    //    sf::Transformable actualPosition=sf::Transformable();
    //    actualPosition.setPosition(getPosition());
    //    this->entity->Set<sf::Transformable>("Position",actualPosition);
        this->entity->Get<StateMachineAnimation*>("Drawable")->update(delta);

}

void EntityNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    entity->Get<StateMachineAnimation*>("Drawable")->draw(target, states);
}