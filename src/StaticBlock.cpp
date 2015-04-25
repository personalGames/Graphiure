/* 
 * File:   StaticBlock.cpp
 * Author: dorian
 * 
 * Created on 28 de marzo de 2015, 23:44
 */

#include "StaticBlock.h"
#include "Entity.h"
#include "OnCollision.h"
#include "Position.h"
#include <cstdlib>

Entity* StaticBlock::prepareEntity(PropertyManager& parameters) {
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

void StaticBlock::makeOnCollision(IdEntity idObject, OnCollision* onCollision) {
    auto aFunction = [idObject] (MessageCollision * message) {

        Entity* moveEntity = message->entityTwo;
        if(moveEntity->getId()==idObject){
            moveEntity=message->entityOne;
        }

        double x, y;
        x = message->mtv.pushX;
        y = message->mtv.pushY;
        if(message->axisX)

        if (abs(x) < 0.1) {
            x = 0;
        }
        
        if (abs(y) < 0.1) {
            y = 0;
        }
        std::cout << x << " " << y << std::endl;
        moveEntity->Get<Position*>("Position")->setPositionIncrement(static_cast<int> (x), static_cast<int> (y));

    };
    //guardo la función creada
    onCollision->onCollisionFunction = aFunction;
}