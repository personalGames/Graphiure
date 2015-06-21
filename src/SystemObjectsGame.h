/* 
 * File:   SystemObjectsGame.h
 * Author: dorian
 *
 * Created on 22 de marzo de 2015, 19:09
 */

#ifndef SYSTEMOBJECTSGAME_H
#define	SYSTEMOBJECTSGAME_H

#include "ISystem.h"
#include "IdEntity.h"
#include "SystemManager.h"
#include "HashIdEntity.h"
#include "Entity.h"
#include "Subject.h"
#include <SFML/System/NonCopyable.hpp>
#include <unordered_map>
#include <list>

/**
 * Sistema de entidades del juego
 */
class SystemObjectsGame : public ISystem, sf::NonCopyable {
public:
    /**
     * Constructor
     * @param systemManager gestor de sistemas
     */
    SystemObjectsGame(SystemManager& systemManager);
    /**
     * Destructor
     */
    virtual ~SystemObjectsGame();
    

    virtual void initialize();
    virtual void finalize();
    virtual void registerEntity(Entity* entity);
    virtual void removedEntity(Entity* entity){};

    virtual void update(sf::Time dt);
    virtual void updateSecondPart(sf::Time dt){};
    
    /**
     * Devuelve el objeto vigilado del patrón observer
     * @return 
     */
    Subject* getMessageEntities() const {
        return messageEntities;
    }
    
    /**
     * Devuelve la entidad solicitada
     * @param id identificador de la entidad solicitada
     * @return la entidad solicitada, si no lo encuentra, salta excepción
     */
    Entity* getEntity(IdEntity id);
    /**
     * Devuelve la entidad solicitada
     * @param id identificador del xml de la entidad solicitada
     * @return la entidad solicitada, si no lo encuentra, salta excepción
     */
    Entity* getEntityXml(IdEntity id);
    /**
     * Borra una entidad
     * @param id identificador de la entidad
     */
    void destroyEntity(IdEntity id);
    
private:
    /**
     * Agrega una nueva entidad
     * @param entity entidad a agregar
     */
    void newEntity(Entity* entity);
    /**
     * Mapeo entre identificadores y entidades
     */
    std::unordered_map<IdEntity, Entity*, HashIdEntity> entities;
    /**
     * Lista de entidades a borrar
     */
    std::list<Entity*> removedEntities;
    /**
     * Gestor de sistemas
     */
    SystemManager* systemManager;
    /**
     * Objeto vigilado en el patrón observer
     */
    Subject* messageEntities;
    /**
     * Lista entre identidades dadas por el motor e identidades dadas en xml
     */
    std::unordered_map<IdEntity, IdEntity, HashIdEntity> entitiesXml;
};

#endif	/* SYSTEMOBJECTSGAME_H */

