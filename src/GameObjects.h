/* 
 * File:   FactoryGameObjects.h
 * Author: dorian
 *
 * Created on 30 de marzo de 2015, 20:47
 */

#ifndef GAMEOBJECTS_H
#define	GAMEOBJECTS_H

#include "PropertyManager.h"
#include "Entity.h"

class GameObjects {
public:
    virtual ~GameObjects() {}

    virtual Entity* prepareEntity(PropertyManager& parameters)=0;
};

#endif	/* GAMEOBJECTS_H */

