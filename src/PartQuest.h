/* 
 * File:   PartQuest.h
 * Author: dorian
 *
 * Created on 7 de mayo de 2015, 11:26
 */

#ifndef PARTQUEST_H
#define	PARTQUEST_H

#include "TypeQuest.h"
#include "IdEntity.h"
#include "Actions.h"
#include <iostream>

/**
 * Parte de una mision
 */
class PartQuest {
public:
    /**
     * Constructor
     * @param type tipo de mision
     * @param destiny entidad de destino afectado
     * @param origin entidad de origen afectado
     */
    PartQuest(TypeQuest type, IdEntity destiny, IdEntity origin);
    /**
     * Constructor
     * @param type tipo de mision
     * @param destiny entidad de destino afectado
     * @param origin entidad de origen afectado
     * @param action accion concreta cuando se especifica el tipo de mision ACTION
     */
    PartQuest(TypeQuest type, IdEntity destiny, IdEntity origin, Actions action);
    /**
     * Constructor copia
     * @param orig
     */
    PartQuest(const PartQuest& orig);
    virtual ~PartQuest();
    
    /**
     * Devuelve la accion concreta
     * @return accion
     */
    inline Actions getAction() const {
        return action;
    }

    /**
     * Setea la accion concreta que es cuando el tipo de mision es ACTION
     * @param action
     */
    inline void setAction(Actions action) {
        this->action = action;
    }

    /**
     * Devuelve el id de la entidad destino afectada
     * @return el id de la entidad destino afectada
     */
    inline IdEntity getIdDestiny() const {
        return idDestiny;
    }

    /**
     * Setea el id de la entidad destino afectada
     * @param idDestiny el id de la entidad destino afectada
     */
    inline void setIdDestiny(IdEntity idDestiny) {
        this->idDestiny = idDestiny;
    }

    /**
     * Devuelve el id de la entidad origen afectada
     * @return el id de la entidad origen afectada
     */
    inline IdEntity getIdOrigin() const {
        return idOrigin;
    }

    /**
     * Setea el id de la entidad origen afectada
     * @param idOrigin el id de la entidad origen afectada
     */
    inline void setIdOrigin(IdEntity idOrigin) {
        this->idOrigin = idOrigin;
    }

    /**
     * Devuelve el tipo de mision
     * @return tipo de mision
     */
    inline TypeQuest getType() const {
        return type;
    }

    /**
     * Setea el tipo de mision
     * @param type tipo de mision
     */
    inline void setType(TypeQuest type) {
        this->type = type;
    }

    /**
     * Indica si está hecho
     * @return true si está hecho
     */
    inline bool isDone() const {
        return done;
    }

    /**
     * Setea si la parte de misión está hecha
     * @param done true si está hecho
     */
    inline void setDone(bool done) {
        this->done = done;
    }
    
private:
    /**
     * Tipo de mision
     */
    TypeQuest type;
    /**
     * Entidad destino
     */
    IdEntity idDestiny;
    /**
     * Entidad origen
     */
    IdEntity idOrigin;
    /**
     * Acción concreta para cuando el tipo de mision es ACTION
     */
    Actions action;
    /**
     * Si se ha hecho o no
     */
    bool done;
    
    
};

#endif	/* PARTQUEST_H */

