/* 
 * File:   Villager.h
 * Author: dorian
 *
 * Created on 1 de abril de 2015, 17:46
 */

#ifndef VILLAGER_H
#define	VILLAGER_H

#include "GameObjects.h"
#include "Entity.h"
#include "Position.h"
#include "Collision.h"
#include "StructCollision.h"
#include "Velocity.h"
#include "StateMachineAnimation.h"
#include "Life.h"
#include "OnCollision.h"
#include "Behaviour.h"
#include "Talk.h"
#include "Questeable.h"
#include "Message.h"

/**
 * Constructor para un aldeano
 */
class Villager : public GameObjects{
public:
    /**
     * Constructor por defecto
     */
    Villager();
    
    /**
     * Devuelve una entidad que define un aldeano dado unos parámetros
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
    /**
     * Define el comportamiento de esta entidad ante las acciones de otra entidad
     * @param behaviour estructura donde dejar la función que se ejecutará
     * @param entity la entidad creada
     */
    void makeBehaviour(Behaviour* behaviour, Entity* entity);
    /**
     * Reacción ante las acciones de otra entidad y establecer si cumple o no las misiones
     * @param quest estructura donde tiene los datos
     * @param entity entidad afectada
     * @param action acción realizada
     */
    void processQuest(Questeable* quest, Entity* entity, Actions action);
};

#endif	/* VILLAGER_H */

