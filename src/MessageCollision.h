/* 
 * File:   MessageCollision.h
 * Author: dorian
 *
 * Created on 19 de marzo de 2015, 11:40
 */

#ifndef MESSAGECOLLISION_H
#define	MESSAGECOLLISION_H

#include "IdEntity.h"

struct MessageCollision {
    MessageCollision(IdEntity one, IdEntity two): one(one),two(two){};
    virtual ~MessageCollision(){};
    
    IdEntity one;
    IdEntity two;
    //more about the collision

};

#endif	/* MESSAGECOLLISION_H */

