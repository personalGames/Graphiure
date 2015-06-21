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

/**
 * Clase base de un sistema
 */
class ISystem {
public:
    ISystem();
    virtual ~ISystem();
    
    /**
     * Devuelve el tipo del sistema
     * @return 
     */
    inline TypeSystem getType(){
        return type;
    }
    
    /**
     * Inicializa el sistema
     */
    virtual void initialize(){
        initialized=true;
    };
    /**
     * Finaliza el sistema
     */
    virtual void finalize(){
        finalized=true;
    };
    /**
     * Actualiza el sistema en una primera tanda
     * @param dt tiempo entre frame y frame
     */
    virtual void update(sf::Time dt){};
    /**
     * Actualiza el sistema en una segunda tanda
     * @param dt tiempo entre frame y frame
     */
    virtual void updateSecondPart(sf::Time dt){};
    /**
     * Registra una entidad en el sistema si es de su incumbencia
     * @param entity entidad a registrar
     */
    virtual void registerEntity(Entity* entity)=0;
    /**
     * Elimina la entidad del sistema
     * @param entity
     */
    virtual void removedEntity(Entity* entity)=0;
    /**
     * Devuele si el sistema ya finalizó
     * @return true si ha finalizado
     */
    inline bool isFinalized() const {
        return finalized;
    }

    /**
     * Devuelve si el sistema ya está inicializado
     * @return true si está inicializado
     */
    inline bool isInitialized() const {
        return initialized;
    }

protected:
    /**
     * Tipo del sistema
     */
    TypeSystem type;
    
private:
    /**
     * Si esta inicializado
     */
    bool initialized;
    /**
     * Si esta finalizado
     */
    bool finalized;
};

#endif	/* ISYSTEM_H */

