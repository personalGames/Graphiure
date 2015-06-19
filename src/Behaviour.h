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
#include "PropertyManager.h"


struct Behaviour {
    Behaviour() {}
    std::function<void(Actions action, PropertyManager* prop)> behaviourFunction;

};

#endif	/* BEHAVIOUR_H */

