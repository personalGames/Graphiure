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
    Entity* entity=new Entity();
    
    Collision* colli=new Collision();
    sf::Vector2f pos=parameters.Get<sf::Vector2f>("Position");
    Position* position=new Position();
    position->updatePosition(pos.x,pos.y);
    
    sf::Transformable transform=position->getPosition();
    colli->update(transform);
    colli->setArrayVertex(parameters.Get<sf::VertexArray*>("Vertex"));
    colli->applyRatio(parameters.Get<sf::Vector2f>("Ratio"));
    colli->setType(TypeCollision::STATIC);
    
    position->setPosition(colli->getTransform());
    
    entity->Add<Position*>("Position", position);
    entity->Add<Collision*>("Collision", colli);
    
    entity->Add<Collision*>("Debug", colli);
    
    Behaviour* behaviour=new Behaviour();
    makeBehaviour(entity->getId(), behaviour);
    entity->Add<Behaviour*>("Behaviour", behaviour);
    
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
        
        Collision* collisionOne = me->Get<Collision*>("Collision");
        Collision* collisionTwo = other->Get<Collision*>("Collision");
        
        if(collisionTwo->getType()==TypeCollision::STATIC){   
            return;
        }
        
        Position* positionTwo = other->Get<Position*>("Position");
        sf::Vector2f separation = collisionOne->normalSeparation(collisionTwo, positionTwo->getMoveVector());

        positionTwo->updatePosition(separation.x, separation.y);
        positionTwo->updatePosition(0,0);
    };

    //guardo la función creada
    behaviour->behaviourFunction = aFunction;
}
