/* 
 * File:   Hole.cpp
 * Author: dorian
 * 
 * Created on 30 de marzo de 2015, 17:53
 */

#include "Hole.h"
#include "Velocity.h"
#include <iostream>

void Hole::makeOnCollision(IdEntity idObject, OnCollision* onCollision) {
    auto aFunction = [idObject] (MessageCollision * message) {
        Entity* other = message->entityOne;
        if (other->getId() == idObject) {
            other = message->entityTwo;
        }
        //le dañamos
        if (other->HasID("Life")) {
            Life* life = other->Get<Life*>("Life");
            life->damage(life->getActualLife());
            if (!life->isAlive()) {
                other->Get<Velocity*>("Velocity")->setFreeze(true);
                other->Get<StateMachineAnimation*>("Drawable")->update(Actions::Dead);
            }
        }
    };

    //guardo la función creada
    onCollision->onCollisionFunction = aFunction;

}

Entity* Hole::prepareEntity(PropertyManager& parameters) {
    Entity* entity = new Entity();

    Collision* colli = new Collision();
    sf::Vector2f pos = parameters.Get<sf::Vector2f>("Position");
    Position* position = new Position();
    position->updatePosition(pos.x, pos.y);

    sf::Transformable transform = position->getPosition();
    colli->update(transform);
    colli->setArrayVertex(parameters.Get<sf::VertexArray*>("Vertex"));
    colli->applyRatio(parameters.Get<sf::Vector2f>("Ratio"));
    colli->setType(TypeCollision::STATIC);

    position->setPosition(colli->getTransform());

    entity->Add<Position*>("Position", position);
    entity->Add<Collision*>("Collision", colli);

    entity->Add<Collision*>("Debug", colli);

    OnCollision* onCollision = new OnCollision();
    makeOnCollision(entity->getId(), onCollision);
    entity->Add<OnCollision*>("OnCollision", onCollision);

    return entity;
}
