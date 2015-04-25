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

    OnCollision* onCollision = new OnCollision();
    makeOnCollision(entity->getId(), onCollision);
    entity->Add<OnCollision*>("OnCollision", onCollision);

    Behaviour* behaviour=new Behaviour();
    makeBehaviour(behaviour);
    entity->Add<Behaviour*>("Behaviour", behaviour);

    return entity;
}

void Villager::makeOnCollision(IdEntity idObject, OnCollision* onCollision) {
    auto aFunction = [idObject] (MessageCollision * message) {

        Entity* moveEntity = message->entityTwo;
        if (moveEntity->getId() == idObject) {
            moveEntity = message->entityOne;
        }

        double x, y;
        x = message->mtv.pushX;
        y = message->mtv.pushY;
        if (message->axisX)

            if (abs(x) < 0.1) {
                x = 0;
            }

        if (abs(y) < 0.1) {
            y = 0;
        }
        std::cout << x << " " << y << std::endl;
        moveEntity->Get<Position*>("Position")->setPositionIncrement(x, y);
    };

    //guardo la función creada
    onCollision->onCollisionFunction = aFunction;
}

void Villager::makeBehaviour(Behaviour* behaviour) {
    auto function = [] (Actions action) {
        std::cout<<"Hola, soy un anciano niño"<<std::endl;
    };
    
    behaviour->behaviourFunction = function;
}

