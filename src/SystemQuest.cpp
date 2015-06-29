/* 
 * File:   SystemQuest.cpp
 * Author: dorian
 * 
 * Created on 7 de mayo de 2015, 12:59
 */

#include "SystemQuest.h"
#include "Quest.h"
#include "MissionStatus.h"

SystemQuest::SystemQuest() {
    type = TypeSystem::QUEST;
}

SystemQuest::~SystemQuest() {
}

void SystemQuest::addQuest(Quest* quest) {
    this->quests.insert(std::pair<int, Quest*>(quest->getId(), quest));
}

void SystemQuest::update(sf::Time dt) {
    //actualizo todas las entidades
    auto it = quests.begin();
    while (it != quests.end()) {
        it->second->update(dt);
        ++it;
    }
}

MissionStatus SystemQuest::getStatus() {
    return MissionStatus::MissionSuccess;
}

void SystemQuest::resetMissions() {
    auto it = quests.begin();
    while (it != quests.end()) {
        it->second->resetQuest();
        ++it;
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

sf::String* SystemQuest::toString() {
    sf::String result = "";
    auto it = quests.begin();
    int i = 1;
    while (it != quests.end()) {
        if (it->second->isOpened()) {
            result += std::to_string(i);
            result += ". ";
            result += *(it->second->getText());
            result += " => ";
            if (it->second->isFinished()) {
                result += "Hecho.";
            } else {
                result += "Sin finalizar";
            }
            result += "\n";
            it++;
            i++;
        }
    }
    sf::String* finalResult = new sf::String(result);
    return finalResult;
}