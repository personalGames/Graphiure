/* 
 * File:   StaticBlock.h
 * Author: dorian
 *
 * Created on 28 de marzo de 2015, 23:44
 */

#ifndef STATICBLOCK_H
#define	STATICBLOCK_H

#include "Entity.h"
#include "Collision.h"
#include "MessageCollision.h"
#include "OnCollision.h"
#include "GameObjects.h"

/**
 * Constructor de una entidad concreta, un objeto del juego
 * define un bloque transparente que no se puede atravesar
 */
class StaticBlock : public GameObjects {
public:
    virtual ~StaticBlock() {

    }

    /**
     * Devuelve una entidad que define un bloque invisible que no se puede atravesar
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

#endif	/* STATICBLOCK_H */

