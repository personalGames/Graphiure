/* 
 * File:   Entity2.h
 * Author: dorian
 *
 * Created on 3 de marzo de 2015, 9:30
 */

#ifndef ENTITY2_H
#define	ENTITY2_H

#include "PropertyManager.h"
#include "IdEntity.h"

//TODO id of the entity

class Entity : public PropertyManager{
public:
    Entity();
    virtual ~Entity();
    
    inline IdEntity getId() const {
        return id;
    }

    inline void setId(IdEntity id) {
        this->id = id;
    }

    
private:
    IdEntity id;
};

#endif	/* ENTITY2_H */

