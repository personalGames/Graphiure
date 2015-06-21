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

/**
 * Clase base para todos los objetos del juego
 */
class GameObjects {
public:
    virtual ~GameObjects() {}

    /**
     * Devuelve una entidad que define objeto del juego
     * @param parameters conjunto de parámetros
     * @return entidad formada
     */
    virtual Entity* prepareEntity(PropertyManager& parameters)=0;
};

#endif	/* GAMEOBJECTS_H */

