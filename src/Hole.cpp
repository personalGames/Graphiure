/* 
 * File:   Hole.cpp
 * Author: dorian
 * 
 * Created on 30 de marzo de 2015, 17:53
 */

#include "Hole.h"



void Hole::makeBehaviour(IdEntity idObject, Behaviour* behaviour) {
    auto aFunction = [idObject] (MessageCollision message) {
        Entity* other=message.entityOne;
        Entity* me=message.entityTwo;
        if(other->getId()==idObject){
            me=other;
            other=message.entityTwo;
        }
        //le dañamos
        if(other->HasID("Life")){
            Life* life=other->Get<Life*>("Life");
            life->damage(life->getActualLife());
            //life->damage(1);
        }
    };
    
    //guardo la función creada
    behaviour->behaviourFunction=aFunction;
}

Entity* Hole::prepareEntity(Collision* coli) {
    Entity* entity=new Entity();
    
    Position* position=new Position();
    position->setPosition(*(coli->getTransform()));
    entity->Add<Position*>("Position", position);
    entity->Add<Collision*>("Collision", coli);
    
    Behaviour* behaviour=new Behaviour();
    makeBehaviour(entity->getId(), behaviour);
    entity->Add<Behaviour*>("Behaviour", behaviour);
    
    return entity;
}
