/* 
 * File:   SystemManager.cpp
 * Author: dorian
 * 
 * Created on 21 de marzo de 2015, 19:54
 */

#include <vector>

#include "SystemManager.h"

SystemManager::SystemManager() : systems() {
    
}

SystemManager::~SystemManager() {
}

void SystemManager::addSystem(ISystem* system) {
    systems.push_back(system);
}

void SystemManager::initializeAll() {
    for (std::vector<ISystem*>::iterator it = systems.begin(); it != systems.end(); ++it) {
        (*it)->initialize();
    }
}

void SystemManager::registerEntity(Entity* entity) {
    for (std::vector<ISystem*>::iterator it = systems.begin(); it != systems.end(); ++it) {
        (*it)->registerEntity(entity);
    }
}

void SystemManager::removeEntity(Entity* entity) {
    for (std::vector<ISystem*>::iterator it = systems.begin(); it != systems.end(); ++it) {
        (*it)->removedEntity(entity);
    }
}


ISystem* SystemManager::getSystem(TypeSystem type) {
    ISystem* system=nullptr;
    for (std::vector<ISystem*>::iterator it = systems.begin(); 
            it != systems.end() && system==nullptr; ++it) {
        if((*it)->getType()==type){
            system=*it;
        }
    }
    return system;
}


void SystemManager::updateAll(sf::Time dt) {
    for (std::vector<ISystem*>::iterator it = systems.begin(); it != systems.end(); ++it) {
        (*it)->update(dt);
    }
}

void SystemManager::finalizeAll() {
    for (std::vector<ISystem*>::iterator it = systems.begin(); it != systems.end(); ++it) {
        (*it)->finalize();
    }
}

void SystemManager::clearSystems() {
    std::vector<ISystem*>::iterator it = systems.begin();
    while (it != systems.end()) {
        if ((*it)->isFinalized()) {
            it = systems.erase(it);
        } else {
            ++it;
        }
    }
}
