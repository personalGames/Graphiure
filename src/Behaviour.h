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

/**
 * Estructura de comportamiento que guarda una función a ejecutar
 */
struct Behaviour {
    Behaviour() {}
    /**
     * Guarda una función que especifica la acción realizada y una serie de
     * propiedades
     */
    std::function<void(Actions action, PropertyManager* prop)> behaviourFunction;

};

#endif	/* BEHAVIOUR_H */

