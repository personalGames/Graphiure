/* 
 * File:   MessageCollision.h
 * Author: dorian
 *
 * Created on 19 de marzo de 2015, 11:40
 */

#ifndef MESSAGECOLLISION_H
#define	MESSAGECOLLISION_H

#include "Entity.h"
#include "TypeCollision.h"

struct MessageCollision {
    MessageCollision(Entity* one, Entity* two): entityOne(one),entityTwo(two){};
    virtual ~MessageCollision(){};
    
    Entity* entityOne;
    Entity* entityTwo;
    //type collision
    
};

#endif	/* MESSAGECOLLISION_H */

