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
#include <unordered_map>
#include "SystemManager.h"
#include "HashIdEntity.h"
#include <SFML/System/NonCopyable.hpp>

class SystemObjectsGame : public ISystem, sf::NonCopyable {
public:
    SystemObjectsGame(SystemManager& systemManager);
    virtual ~SystemObjectsGame();
    

    virtual void initialize();
    virtual void finalize();
    virtual void registerEntity(Entity* entity);
    virtual void removedEntity(Entity* entity){};

    virtual void update(sf::Time dt);
    virtual void updateSecondPart(sf::Time dt){};
    
    
    Entity* getEntity(IdEntity id);
    void destroyEntity(IdEntity id);
    
private:
    void newEntity(Entity* entity);
    std::unordered_map<IdEntity, Entity*, HashIdEntity> entities;
    std::list<Entity*> removedEntities;
    SystemManager* systemManager;
};

#endif	/* SYSTEMOBJECTSGAME_H */

