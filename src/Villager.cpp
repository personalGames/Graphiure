/* 
 * File:   Villager.cpp
 * Author: dorian
 * 
 * Created on 1 de abril de 2015, 17:46
 */

#include "Villager.h"

Villager::Villager() {
}

Entity* Villager::prepareEntity(PropertyManager& parameters) {
    Entity* entity = new Entity(Category::CHARACTER);

    if (parameters.HasID("MaxVelocity")) {
        Velocity* vel = new Velocity();
        vel->setMaxVelocity(parameters.Get<float>("MaxVelocity"));
        entity->Add<Velocity*>("Velocity", vel);
    }

    //entity->Add<bool>("Commandable", true);

    if (parameters.HasID("Life")) {
        Life* life = new Life(parameters.Get<float>("Life"));
        entity->Add<Life*>("Life", life);
    }

    Position* position = new Position();
    sf::Vector2f pos;
    if (parameters.HasID("Position")) {
        pos = parameters.Get<sf::Vector2f>("Position");
        position->updatePosition(pos.x, pos.y);
    }


    if (parameters.HasID("Collision")) {
        StructCollision* colliStruct = parameters.Get<StructCollision*>("Collision");

        Collision* colli = new Collision();
        if (!parameters.HasID("Position")) {
            pos = colliStruct->position;
            position->updatePosition(pos.x, pos.y);
        }

        sf::Transformable transform = position->getPosition();
        colli->update(transform);
        colli->setArrayVertex(colliStruct->vertices);
        if (parameters.HasID("Ratio")) {
            colli->applyRatio(parameters.Get<sf::Vector2f>("Ratio"));
        }
        colli->setType(TypeCollision::DYNAMIC);
        position->setPosition(colli->getTransform());
        
        delete colliStruct;
        entity->Add<Collision*>("Collision", colli);
    }

    entity->Add<Position*>("Position", position);
    

    if (parameters.HasID("Drawable")) {
        StateMachineAnimation* animations = parameters.Get<StateMachineAnimation*>("Drawable");
        entity->Add<StateMachineAnimation*>("Drawable", animations);
    }
    
//    if(parameters.HasID("Talk")){
//        Behaviour* behaviour=new Behaviour();
//        makeBehaviour(entity->getId(), behaviour);
//        entity->Add<Behaviour*>("Behaviour", behaviour);
//    }
    
    return entity;
}

void Villager::makeBehaviour(IdEntity idObject, Behaviour* behaviour) {
    auto aFunction = [idObject] (MessageCollision message) {
//        Entity* other = message.entityOne;
//        Entity* me = message.entityTwo;
//        if (other->getId() == idObject) {
//            me = other;
//            other = message.entityTwo;
//        }
//
//        Collision* collisionOne = me->Get<Collision*>("Collision");
//        Collision* collisionTwo = other->Get<Collision*>("Collision");
//        Position* positionTwo = other->Get<Position*>("Position");
//        sf::Vector2f separation = collisionOne->normalSeparation(collisionTwo, sf::Vector2f(0,0));
//
//        positionTwo->updatePosition(separation.x, separation.y);
    };

    //guardo la función creada
    behaviour->behaviourFunction = aFunction;
}
