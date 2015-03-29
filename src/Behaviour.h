/* 
 * File:   Behaviour.h
 * Author: dorian
 *
 * Created on 29 de marzo de 2015, 0:35
 */

#ifndef BEHAVIOUR_H
#define	BEHAVIOUR_H

#include "MessageCollision.h"
#include <functional>


struct Behaviour {
    Behaviour() {}
    std::function<void(MessageCollision message)> behaviourFunction;

};

#endif	/* BEHAVIOUR_H */

