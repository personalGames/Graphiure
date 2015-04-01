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
#include "StateMachineAnimation.h"

class Character : public GameObjects{
public:
    virtual ~Character();
    
    virtual Entity* prepareEntity(PropertyManager& parameters);
private:
    
};

#endif	/* CHARACTER_H */

