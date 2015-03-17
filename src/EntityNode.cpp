/* 
 * File:   EntityNode.cpp
 * Author: dorian
 * 
 * Created on 4 de marzo de 2015, 12:22
 */


#include "EntityNode.h"
#include "AnimatedSprite.h"
#include "StateMachineAnimation.h"

EntityNode::EntityNode(Entity* entity): entity(entity) {
}

EntityNode::~EntityNode() {
}

void EntityNode::setVelocity(sf::Vector2f velocity) {
    this->entity->Set<sf::Vector2f>("Velocity",velocity);
}

void EntityNode::setVelocity(float x, float y) {
    this->entity->Set<sf::Vector2f>("Velocity",sf::Vector2f(x,y));
}

void EntityNode::updateCurrent(sf::Time delta, CommandQueue&) {
    adaptVelocity();
    //animatedCharacter.update(dt); actualizar renderizado
    //eso tendría que ir en el sistema de renderizado
    //move is a function of sfml. Adds to the current position by moving
    //an offset unlike setPosition which overwrites it.
    //sf::Vector2f s=velocity * delta.asSeconds();
    sf::Vector2f s=(this->entity->Get<sf::Vector2f>("Velocity"))
                        * delta.asSeconds();
    move(static_cast<int>(s.x), static_cast<int>(s.y));

    sf::Transformable actualPosition=sf::Transformable();
    actualPosition.setPosition(getPosition());
    this->entity->Set<sf::Transformable>("Position",actualPosition);
    this->entity->Get<StateMachineAnimation*>("Drawable")->update(delta);
    
}

float EntityNode::getMaxSpeed() const {
    return this->entity->Get<float>("MaxVelocity");
}


void EntityNode::accelerate(sf::Vector2f velocity) {
    sf::Vector2f previous(this->entity->Get<sf::Vector2f>("Velocity"));
    previous+=velocity;
    this->entity->Set<sf::Vector2f>("Velocity",previous);
}

void EntityNode::accelerate(float vx, float vy) {
    sf::Vector2f previous(this->entity->Get<sf::Vector2f>("Velocity"));
    previous.x += vx;
    previous.y += vy;
    this->entity->Set<sf::Vector2f>("Velocity",previous);
}

void EntityNode::adaptVelocity() {
    sf::Vector2f velocity = this->entity->Get<sf::Vector2f>("Velocity");

    // If moving diagonally, reduce velocity (to have always same velocity)
    if (velocity.x != 0.f && velocity.y != 0.f) {
        this->setVelocity(velocity / std::sqrt(2.f));
        
    //if none, stop the animation
    } else if (velocity.x == 0 && velocity.y == 0) {
        updateAnimation(Actions::None);
    }
}

void EntityNode::updateAnimation(Actions action) {
    this->entity->Get<StateMachineAnimation*>("Drawable")->update(action);
}


unsigned int EntityNode::getCategory() const {
    return Category::CHARACTER;
}

void EntityNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    entity->Get<StateMachineAnimation*>("Drawable")->draw(target,states);
}

void EntityNode::onCommand(const Command& command, sf::Time delta) {
    // Command current node, if category matches
    if ((command.category & this->getCategory())>=1) {
        command.action(*this, delta);
    }

    // Propagate command to children
    for (SceneNode* child : children) {
        child->onCommand(command, delta);
    }
}