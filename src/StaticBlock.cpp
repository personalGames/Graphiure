/* 
 * File:   StaticBlock.cpp
 * Author: dorian
 * 
 * Created on 28 de marzo de 2015, 23:44
 */

#include "StaticBlock.h"
#include "Entity.h"
#include "Behaviour.h"

StaticBlock::StaticBlock(Collision* coli): coli(coli) {
}

StaticBlock::~StaticBlock() {
}

Entity* StaticBlock::prepareEntity() {
    Entity* entity=new Entity();
    
    entity->Add<sf::Transformable*>("Position", coli->getTransform());
    entity->Add<Collision*>("Collision", coli);
    
    Behaviour* behaviour=new Behaviour();
    makeBehaviour(entity->getId(), behaviour);
    
    return entity;
}

void StaticBlock::makeBehaviour(IdEntity idObject, Behaviour* behaviour) {
    auto aFunction = [idObject] (MessageCollision message) {
        Entity* other=message.one;
        Entity* me=message.two;
        if(other->getId()==idObject){
            me=other;
            other=message.two;
        }
        //mandar a tomar por saco a other para evitar la colisión
    };
    
    //guardo la función creada
    behaviour->behaviourFunction=aFunction;
}
