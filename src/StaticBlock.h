/* 
 * File:   StaticBlock.h
 * Author: dorian
 *
 * Created on 28 de marzo de 2015, 23:44
 */

#ifndef STATICBLOCK_H
#define	STATICBLOCK_H

#include "Entity.h"
#include "Collision.h"
#include "MessageCollision.h"
#include "Behaviour.h"

class StaticBlock {
public:
    StaticBlock(Collision* coli);
    virtual ~StaticBlock();
    
    Entity* prepareEntity();
    
private:
    Collision* coli;
    
    void makeBehaviour(IdEntity idObject, Behaviour* behaviour);
};

#endif	/* STATICBLOCK_H */

