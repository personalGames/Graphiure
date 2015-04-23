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
#include "Triangle.h"
#include "MTV.h"

struct MessageCollision {
    MessageCollision(): entityOne(nullptr), entityTwo(nullptr), axisX(false), toRightDown(false){}
    MessageCollision(Entity* one, Entity* two): entityOne(one),entityTwo(two),
                        axisX(false),toRightDown(false) {};
    virtual ~MessageCollision(){};
    
    Entity* entityOne;
    Entity* entityTwo;
    bool axisX;
    bool toRightDown;
    MTV mtv;
    
    
};

#endif	/* MESSAGECOLLISION_H */

