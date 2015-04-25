/* 
 * File:   Behaviour.h
 * Author: dorian
 *
 * Created on 29 de marzo de 2015, 0:35
 */

#ifndef ON_COLLISION_H
#define	ON_COLLISION_H

#include "MessageCollision.h"
#include <functional>


struct OnCollision {
    OnCollision() {}
    std::function<void(MessageCollision* message)> onCollisionFunction;

};

#endif	/* BEHAVIOUR_H */

