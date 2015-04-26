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
#include "Position.h"
#include "Collision.h"

EntityNode::EntityNode(Entity* entity) : entity(entity) {
    Transformable trans = (entity->Get<Position*>("Position")->getPosition());
    setOrigin(trans.getOrigin());
    setPosition(trans.getPosition());
    setScale(trans.getScale());
}

EntityNode::~EntityNode() {
}

void EntityNode::updateCurrent(sf::Time delta) {
    if (this->entity->HasID("Velocity")) {
        Velocity* velocity = this->entity->Get<Velocity*>("Velocity");
        if (velocity->isQuiet() && entity->HasID("Drawable")) {
            entity->Get<StateMachineAnimation*>("Drawable")->update(Actions::None);
        }
    }

    Position* position = this->entity->Get<Position*>("Position");
    setPosition(position->getPosition().getPosition());

    this->entity->Get<StateMachineAnimation*>("Drawable")->update(delta);
}

void EntityNode::updateSecondPart(sf::Time dt) {
    Position* position = this->entity->Get<Position*>("Position");
    setPosition(position->getPosition().getPosition());
    
    SceneNode::updateSecondPart(dt);
}


void EntityNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    entity->Get<StateMachineAnimation*>("Drawable")->draw(target, states);
    
    Collision* col=entity->Get<Collision*>("Collision");
    target.draw(*(col->vertices), states);
}