/* 
 * File:   Entity2.h
 * Author: dorian
 *
 * Created on 3 de marzo de 2015, 9:30
 */

#ifndef ENTITY2_H
#define	ENTITY2_H

#include "PropertyManager.h"

class Entity2 {
public:
    Entity2();
    Entity2(const Entity2& orig);
    virtual ~Entity2();
    
    PropertyManager getProperties();
    
    
private:
    PropertyManager properties;
};

#endif	/* ENTITY2_H */

