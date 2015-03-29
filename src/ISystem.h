/* 
 * File:   ISystem.h
 * Author: dorian
 *
 * Created on 22 de marzo de 2015, 14:09
 */

#ifndef ISYSTEM_H
#define	ISYSTEM_H

#include "Entity.h"
#include "TypeSystem.h"
#include <SFML/System/Time.hpp>

class ISystem {
public:
    ISystem();
    virtual ~ISystem();
    
    inline TypeSystem getType(){
        return type;
    }
    
    virtual void initialize(){
        initialized=true;
    };
    virtual void finalize(){
        finalized=true;
    };
    virtual void update(sf::Time dt){};
    virtual void updateSecondPart(sf::Time dt){};
    
    virtual void registerEntity(Entity* entity)=0;
    virtual void removedEntity(Entity* entity)=0;
    
    inline bool isFinalized() const {
        return finalized;
    }

    inline bool isInitialized() const {
        return initialized;
    }

protected:
    TypeSystem type;
    
private:
    bool initialized;
    bool finalized;
};

#endif	/* ISYSTEM_H */

