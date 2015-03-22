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

class SystemManager {
public:
    SystemManager();
    virtual ~SystemManager();
    
    void addSystem(ISystem* system);
    void initializeAll();
    void finalizeAll();
    void updateAll();
    void clearSystems();
    void registerEntity(Entity* entity);
    void removeEntity(Entity* entity);
    
    ISystem* getSystem(TypeSystem type);
    
private:
    std::vector<ISystem*> systems;
};

#endif	/* SYSTEMMANAGER_H */

