/* 
 * File:   Hole.cpp
 * Author: dorian
 * 
 * Created on 30 de marzo de 2015, 17:53
 */

#include "Hole.h"
#include <iostream>

void Hole::makeBehaviour(IdEntity idObject, Behaviour* behaviour) {
    auto aFunction = [idObject] (MessageCollision* message) {
        Entity* other=message->entityOne;
        //Entity* me=message.entityTwo;
        if(other->getId()==idObject){
            //me=other;
            other=message->entityTwo;
        }
        //le dañamos
        if(other->HasID("Life")){
            std::cout<<"Touched"<<std::endl;
            Life* life=other->Get<Life*>("Life");
            life->damage(life->getActualLife());
            //life->damage(1);
        }
    };
    
    //guardo la función creada
    behaviour->behaviourFunction=aFunction;
    
}

Entity* Hole::prepareEntity(PropertyManager& parameters) {
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
