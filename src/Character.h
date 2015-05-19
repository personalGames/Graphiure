/* 
 * File:   Character.h
 * Author: dorian
 *
 * Created on 1 de abril de 2015, 13:28
 */

#ifndef CHARACTER_H
#define	CHARACTER_H

#include "GameObjects.h"
#include "Entity.h"
#include "Life.h"
#include "Position.h"
#include "Collision.h"
#include "StructCollision.h"
#include "Velocity.h"
#include "Weapon.h"
#include "StateMachineAnimation.h"
#include "Behaviour.h"
#include "GameStates.h"

class Character : public GameObjects{
public:
    virtual ~Character();
    
    virtual Entity* prepareEntity(PropertyManager& parameters);
private:
    void makeBehaviour(Behaviour* behaviour, Entity* entity);
};

#endif	/* CHARACTER_H */

