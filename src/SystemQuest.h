/* 
 * File:   SystemQuest.h
 * Author: dorian
 *
 * Created on 7 de mayo de 2015, 12:59
 */

#ifndef SYSTEMQUEST_H
#define	SYSTEMQUEST_H

#include "ISystem.h"
#include "Quest.h"
#include "Entity.h"
#include <unordered_map>
#include <SFML/System/NonCopyable.hpp>

class SystemQuest : public ISystem, sf::NonCopyable {
public:
    SystemQuest();
    virtual ~SystemQuest();
    
    virtual void initialize();
    virtual void finalize();
    virtual void registerEntity(Entity* entity);
    virtual void removedEntity(Entity* entity);;

    virtual void update(sf::Time dt);
    virtual void updateSecondPart(sf::Time dt){};
    
    void addQuest(Quest* quest);
    
private:
    std::vector<Entity*> entities;
    std::unordered_map<int, Quest*> quests;
};

#endif	/* SYSTEMQUEST_H */

