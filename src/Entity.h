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
#include "Category.h"

//TODO id of the entity

class Entity : public PropertyManager{
public:
    Entity();
    Entity(Category category);
    virtual ~Entity();
    
    inline IdEntity getId() const {
        return id;
    }

    inline void setId(IdEntity id) {
        this->id = id;
    }
    
    bool isDestroyed() const {
        return destroyed;
    }

    inline void destroy(){
        destroyed=true;
    }
    
    inline Category getCategory() const {
        return category;
    }


    
private:
    IdEntity id;
    bool destroyed;
    Category category;
};

#endif	/* ENTITY2_H */

