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

    Behaviour* behaviour = new Behaviour();
    makeBehaviour(entity->getId(), behaviour);
    entity->Add<Behaviour*>("Behaviour", behaviour);

    return entity;
}

void StaticBlock::makeBehaviour(IdEntity idObject, Behaviour* behaviour) {
    auto aFunction = [idObject] (MessageCollision * message) {

//        Entity* staticEntity = message->entityOne;
        Entity* moveEntity = message->entityTwo;

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
        moveEntity->Get<Position*>("Position")->updatePosition(x, y);

    };
    //guardo la función creada
    behaviour->behaviourFunction = aFunction;
}