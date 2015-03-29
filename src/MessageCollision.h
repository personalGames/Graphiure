/* 
 * File:   MessageCollision.h
 * Author: dorian
 *
 * Created on 19 de marzo de 2015, 11:40
 */

#ifndef MESSAGECOLLISION_H
#define	MESSAGECOLLISION_H

#include "Entity.h"

struct MessageCollision {
    MessageCollision(Entity* one, Entity* two): one(one),two(two){};
    virtual ~MessageCollision(){};
    
    Entity* one;
    Entity* two;
};

#endif	/* MESSAGECOLLISION_H */

