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

/**
 * Entidad
 */
class Entity : public PropertyManager{
public:
    /**
     * Constructor
     */
    Entity();
    /**
     * Constructor en el que se puede especificar la categoría a la que pertenece
     * @param category categoria al que pertenece
     */
    Entity(Category category);
    /**
     * Destructor
     */
    virtual ~Entity();
    
    /**
     * Devuelve el identificador de la entidad
     * @return identificador de la entidad
     */
    inline IdEntity getId() const {
        return id;
    }

    /**
     * Setea el identificador de la entidad
     * @param id nuevo identificador
     */
    inline void setId(IdEntity id) {
        this->id = id;
    }
    
    /**
     * Determina si la entidad está destruida
     * @return true si la entidad está destruida
     */
    bool isDestroyed() const {
        return destroyed;
    }

    /**
     * Setea la entidad como destruida
     */
    inline void destroy(){
        destroyed=true;
    }
    
    /**
     * Devuelve la categoría de la entidad
     * @return categoría de la entidad
     */
    inline Category getCategory() const {
        return category;
    }

    /**
     * Devuelve el identificador de la entidad establecido en el xml de datos
     * @return el identificador del xml de datos. Por defecto, es un id de -1
     */
    inline IdEntity getIdXml() const {
        return idXml;
    }

    /**
     * Setea el identificador de la entidad establecido en el xml de datos
     * @param id el identificador del xml de datos
     */
    inline void setIdXml(IdEntity id) {
        this->idXml = id;
    }

    
private:
    /**
     * Identificador de la entidad
     */
    IdEntity id;
    /**
     * Identificador de la entidad en el xml
     */
    IdEntity idXml;
    /**
     * Variable que guarda si la entidad está destruida
     */
    bool destroyed;
    /**
     * Categoría de la entidad
     */
    Category category;
};

#endif	/* ENTITY2_H */

