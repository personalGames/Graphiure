/* 
 * File:   SystemMovement.cpp
 * Author: dorian
 * 
 * Created on 29 de marzo de 2015, 11:34
 */

#include "SystemMovement.h"

SystemMovement::SystemMovement(): ISystem(), movement() {
    type=TypeSystem::MOVEMENT;
}

void SystemMovement::finalize() {

}

void SystemMovement::initialize() {

}

void SystemMovement::registerEntity(Entity* entity) {
    if (entity->HasID("Velocity")) {
        movement.push_back(entity);
    }
}

void SystemMovement::removedEntity(Entity* entity) {
    movement.erase(std::find(movement.begin(), movement.end(), entity));
}

void SystemMovement::update(sf::Time dt) {
    for(auto entity: movement){
        Velocity* velocity = entity->Get<Velocity*>("Velocity");
        velocity->adaptVelocity();

        sf::Transformable* position = entity->Get<sf::Transformable*>("Position");
        velocity->updateVelocity(dt, *position);
    }
}

void SystemMovement::updateSecondPart(sf::Time dt) {

}

SystemMovement::~SystemMovement() {

}
