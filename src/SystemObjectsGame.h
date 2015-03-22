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
    virtual void registerEntity(Entity* entity){
        //do nothing, this system has his own method to add new entities};
    }
    virtual void removedEntity(Entity* entity){};

    virtual void update();
    virtual void updateSecondPart(){};
    
    void newEntity(Entity* entity);
    Entity* getEntity(IdEntity id);
    void destroyEntity(IdEntity id);
    
private:
    std::unordered_map<IdEntity, Entity*, HashIdEntity> entities;
    std::list<Entity*> removedEntities;
    SystemManager* systemManager;
};

#endif	/* SYSTEMOBJECTSGAME_H */

