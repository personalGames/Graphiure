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

class Villager : public GameObjects{
public:
    Villager();
    
    virtual Entity* prepareEntity(PropertyManager& parameters);
private:
    void makeOnCollision(IdEntity idObject, OnCollision* onCollision);
    void makeBehaviour(Behaviour* behaviour, Entity* entity);
    void processQuest(Questeable* quest, Entity* entity, Actions action);
};

#endif	/* VILLAGER_H */

