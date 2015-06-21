/* 
 * File:   ChangeLevel.h
 * Author: dorian
 *
 * Created on 20 de junio de 2015, 16:29
 */

#ifndef CHANGELEVEL_H
#define	CHANGELEVEL_H

#include "GameObjects.h"
#include "Entity.h"
#include "Collision.h"
#include "OnCollision.h"
#include "Position.h"
#include "Message.h"
#include "Subject.h"
#include "PropertyManager.h"

#include <iostream>

/**
 * Constructor de una entidad concreta, un objeto del juego
 * define una zona que provoca cambios de nivel
 */
class ChangeLevel : public GameObjects {
public:
    virtual ~ChangeLevel();
    
    /**
     * Devuelve una entidad que define una zona que provoca cambios de nivel
     *  dado unos parámetros
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

#endif	/* CHANGELEVEL_H */

