/* 
 * File:   Message.h
 * Author: dorian
 *
 * Created on 27 de abril de 2015, 11:49
 */

#ifndef MESSAGE_H
#define	MESSAGE_H

#include "GameStates.h"
#include "IdEntity.h"
#include <SFML/System/String.hpp>

/**
 * Mensaje intermedio que se utiliza en el patrón observer y provocar
 * cambios en el objeto para notificación
 */
class Message {
public:
    /**
     * Constructor
     */
    Message(){};
    /**
     * Constructor especificando el estado de cambio
     * @param state
     */
    Message(GameStates state):state(state){};
    virtual ~Message();
    
    /**
     * Devuelve el estado asignado
     * @return estado
     */
    inline GameStates getState() const {
        return state;
    }

    /**
     * Setea el estado
     * @param state estado nuevo
     */
    inline void setState(GameStates state) {
        this->state = state;
    }

    /**
     * Devuelve el identificador de la entidad implicada si hubiera
     * @return identificador de la entidad
     */
    IdEntity getIdEntity() const {
        return idEntity;
    }
    
    /**
     * Setea el identificador de la entidad implicada
     * @param id identificador de la entidad
     */
    void setIdEntity(IdEntity id){
        this->idEntity=id;
    }
    
    /**
     * Setea un string de datos arbitrario que pudiera ser de interés al observador
     * @param data string de datos
     */
    inline void setData(std::string* data){
        this->data=data;
    }
    
    /**
     * Devuelve un string de datos arbitario que pudiera ser de interés al observador
     * @return string de datos
     */
    inline std::string* getData(){
        return data;
    }

    
private:
    /**
     * Estado
     */
    GameStates state;
    /**
     * Identificador de la entidad involucrada
     */
    IdEntity idEntity;
    /**
     * String de datos
     */
    std::string* data;
};

#endif	/* MESSAGE_H */

