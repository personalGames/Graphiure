/* 
 * File:   SystemCommand.cpp
 * Author: dorian
 * 
 * Created on 27 de marzo de 2015, 18:08
 */

#include "SystemCommand.h"
#include "Velocity.h"
#include <iostream>

SystemCommand::SystemCommand() : commandable() {
    type=TypeSystem::INPUT;
}

SystemCommand::~SystemCommand() {
}

void SystemCommand::execute() {

}

void SystemCommand::finalize() {
}

void SystemCommand::initialize() {
}

void SystemCommand::registerEntity(Entity* entity) {
    if (entity->HasID("Commandable")) {
        commandable.push_back(entity);
    }
}

void SystemCommand::removedEntity(Entity* entity) {
    commandable.erase(std::find(commandable.begin(), commandable.end(), entity));
    
}

void SystemCommand::update(sf::Time dt) {

}

void SystemCommand::updateSecondPart(sf::Time dt) {

}

void SystemCommand::onCommand(CommandQueue& queue, sf::Time delta) {
//    for (auto &entity : commandable) {
//            entity->Get<Velocity*>("Velocity")->reset();
//        }
    
    
    while (!queue.isEmpty()) {
        const Command& command = queue.pop();
        for (auto &entity : commandable) {
            if ((command.category & entity->getCategory()) >= 1) {
                command.action(*entity, delta);
            }
        }
    }
}
