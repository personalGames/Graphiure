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
#include "StateMachineAnimation.h"
#include "OnCollision.h"
#include "Position.h"
#include "GameObjects.h"

/**
 * Constructor de una entidad concreta, un objeto del juego
 * define un agujero
 */
class Hole : public GameObjects {
public:
    virtual ~Hole() {
    }

    /**
     * Devuelve una entidad que define un agujero dado unos parámetros
     * @param parameters conjunto de parámetros
     * @return entidad formada
     */
    virtual Entity* prepareEntity(PropertyManager& parameters);
private:
    /**
     * Define una función que se ejecutará ante las colisiones contra esta entidad
     * @param idObject id de la entidad recién creada
     * @param onCollision la propiedad de colisión de la entidad
     */
    void makeOnCollision(IdEntity idObject, OnCollision* onCollision);
};

#endif	/* HOLE_H */

