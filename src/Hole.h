/* 
 * File:   Hole.h
 * Author: dorian
 *
 * Created on 30 de marzo de 2015, 17:53
 */

#ifndef HOLE_H
#define	HOLE_H

#include "Collision.h"
#include "PropertyManager.h"
#include "Entity.h"
#include "Life.h"
#include "Behaviour.h"
#include "Position.h"

namespace Hole{
    Entity* prepareEntity(Collision* coli);

    void makeBehaviour(IdEntity idObject, Behaviour* behaviour);
}

#endif	/* HOLE_H */

