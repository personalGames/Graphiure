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

union DataUnion{
    StructMap* map;
    Animation* animation;
    StructAnimation* animations;
    StateMachine* stateMachine;
    std::vector<Collision*>* collisions;
};

#endif	/* DATAUNION_H */

