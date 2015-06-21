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

/**
 * Estructura de colisión en el que guarda una función a ejecutar
 */
struct OnCollision {
    OnCollision() {}
    /**
     * Guarda una función que especifica un mensaje de colisión
     */
    std::function<void(MessageCollision* message)> onCollisionFunction;

};

#endif	/* BEHAVIOUR_H */

