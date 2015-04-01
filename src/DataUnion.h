/* 
 * File:   DataUnion.h
 * Author: dorian
 *
 * Created on 9 de marzo de 2015, 23:16
 */

#ifndef DATAUNION_H
#define	DATAUNION_H

#include "StructMap.h"
#include "StructAnimation.h"
#include "StateMachine.h"
#include <vector>
#include "Collision.h"
#include "StructCollision.h"
#include "PropertyManager.h"

union DataUnion{
    StructMap* map;
    Animation* animation;
    StructAnimation* animations;
    StateMachine* stateMachine;
    std::vector<StructCollision*>* collisions;
    PropertyManager* propertiesEntity;
};

#endif	/* DATAUNION_H */

