/* 
 * File:   SystemManager.h
 * Author: dorian
 *
 * Created on 21 de marzo de 2015, 19:54
 */

#ifndef SYSTEMMANAGER_H
#define	SYSTEMMANAGER_H

#include "ISystem.h"

#include <vector>

/**
 * Gestor de sistemas
 */
class SystemManager {
public:
    SystemManager();
    virtual ~SystemManager();
    
    
    
    void addSystem(ISystem* system);
    void initializeAll();
    void finalizeAll();
    void updateAll(sf::Time dt);
    void clearSystems();
    void registerEntity(Entity* entity);
    void removeEntity(Entity* entity);
    
    /**
     * Devuelve un sistema solicitado
     * @param type tipo del sistema solicitado
     * @return el sistema
     */
    ISystem* getSystem(TypeSystem type);
    
private:
    /**
     * Lista de sistemas
     */
    std::vector<ISystem*> systems;
};

#endif	/* SYSTEMMANAGER_H */

