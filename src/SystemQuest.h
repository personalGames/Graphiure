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
#include "MissionStatus.h"
#include <unordered_map>
#include <SFML/System/String.hpp>
#include <SFML/System/NonCopyable.hpp>

/**
 * Sistema de misiones
 */
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
    
    /**
     * Devuelve el estado de las misiones, de forma que se sepa si ha ganado
     * o perdido el juego, o está en marcha todavía
     * @return estado del juego
     */
    MissionStatus getStatus();
    
    /**
     * Resetea las misiones
     */
    void resetMissions();
    
    /**
     * Añade una nueva misión al sistema
     * @param quest
     */
    void addQuest(Quest* quest);
    /**
     * Devuelve un string representando las missiones y si están completas
     * @return 
     */
    sf::String* toString();
    
private:
    /**
     * Lista de entidades del sistema
     */
    std::vector<Entity*> entities;
    /**
     * Lista de misiones del sistema
     */
    std::unordered_map<int, Quest*> quests;
};

#endif	/* SYSTEMQUEST_H */

