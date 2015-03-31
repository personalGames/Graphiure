/* 
 * File:   StaticBlock.cpp
 * Author: dorian
 * 
 * Created on 28 de marzo de 2015, 23:44
 */

#include "StaticBlock.h"
#include "Entity.h"
#include "Behaviour.h"
#include "Position.h"

Entity* StaticBlock::prepareEntity(PropertyManager& parameters) {
    Entity* entity = new Entity();

//    entity->Add<sf::Transformable*>("Position", coli->getTransform());
//    entity->Add<Collision*>("Collision", coli);
//
//    Behaviour* behaviour = new Behaviour();
//    makeBehaviour(entity->getId(), behaviour);
//    entity->Add<Behaviour*>("Behaviour", behaviour);

    return entity;
}

void StaticBlock::makeBehaviour(IdEntity idObject, Behaviour* behaviour) {
    auto aFunction = [idObject] (MessageCollision message) {
        Entity* other = message.entityOne;
        Entity* me = message.entityTwo;
        if (other->getId() == idObject) {
            me = other;
            other = message.entityTwo;
        }

        Collision* collisionOne = message.entityOne->Get<Collision*>("Collision");
        Collision* collisionTwo = message.entityTwo->Get<Collision*>("Collision");
        Position* positionTwo = message.entityTwo->Get<Position*>("Position");
        sf::Vector2f separation = collisionOne->normalSeparation(collisionTwo);

        positionTwo->updatePosition(separation.x, separation.y);
    };

    //guardo la función creada
    behaviour->behaviourFunction = aFunction;
}
