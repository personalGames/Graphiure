/* 
 * File:   SystemMovement.h
 * Author: dorian
 *
 * Created on 29 de marzo de 2015, 11:34
 */

#ifndef SYSTEMMOVEMENT_H
#define	SYSTEMMOVEMENT_H

#include <vector>
#include "Entity.h"
#include "ISystem.h"
#include <algorithm>
#include "Velocity.h"

class SystemMovement : public ISystem {
public:
    SystemMovement();
    virtual ~SystemMovement();
    
    virtual void initialize();;
    virtual void finalize();;
    virtual void update(sf::Time dt);
    virtual void updateSecondPart(sf::Time dt);
    virtual void registerEntity(Entity* entity);
    virtual void removedEntity(Entity* entity);
    
private:
    std::vector<Entity*> movement;
};

#endif	/* SYSTEMMOVEMENT_H */

