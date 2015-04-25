/* 
 * File:   Behaviour.h
 * Author: dorian
 *
 * Created on 25 de abril de 2015, 16:31
 */

#ifndef BEHAVIOUR_H
#define	BEHAVIOUR_H

#include <functional>
#include "Actions.h"


struct Behaviour {
    Behaviour() {}
    std::function<void(Actions action)> behaviourFunction;

};

#endif	/* BEHAVIOUR_H */

