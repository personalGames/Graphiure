/* 
 * File:   SystemQuest.cpp
 * Author: dorian
 * 
 * Created on 7 de mayo de 2015, 12:59
 */

#include "SystemQuest.h"
#include "Quest.h"

SystemQuest::SystemQuest() {
    
}

SystemQuest::~SystemQuest() {
}

void SystemQuest::addQuest(Quest* quest) {
    this->quests.insert(std::pair<int,Quest*>(quest->getId(), quest));
}

void SystemQuest::update(sf::Time dt) {
    //actualizo todas las entidades
    auto it = quests.begin();
    while (it != quests.end()){
        it->second->update(dt);
    }
}

void SystemQuest::registerEntity(Entity* entity) {
    if (entity->HasID("Questeable")) {
        entities.push_back(entity);
    }
}

void SystemQuest::removedEntity(Entity* entity) {
    entities.erase(std::find(entities.begin(), entities.end(), entity));
}

void SystemQuest::finalize() {

}

void SystemQuest::initialize() {

}
