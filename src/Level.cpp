/* 
 * File:   Level.cpp
 * Author: dorian
 * 
 * Created on 9 de febrero de 2015, 0:08
 */

#include "Level.h"
#include <iostream>

Level::Level(SystemManager& systemManager) :
systemManager(&systemManager) {
    objectsGame = static_cast<SystemObjectsGame*>
            (systemManager.getSystem(TypeSystem::OBJECTS));

    graphics = static_cast<SystemGraphic*>
            (systemManager.getSystem(TypeSystem::GRAPHIC));

    collision = static_cast<SystemCollision*>
            (systemManager.getSystem(TypeSystem::COLLISION));

    commands = static_cast<SystemCommand*>
            (systemManager.getSystem(TypeSystem::INPUT));
}

void Level::setCharacter(IdEntity characterCreated) {
    idCharacter = characterCreated;
}

Level::~Level() {

}

void Level::draw() {
    SystemGraphic* graphics = static_cast<SystemGraphic*>
            (systemManager->getSystem(TypeSystem::GRAPHIC));
    graphics->execute();
}

void Level::update(sf::Time dt) {
    Entity* entity = objectsGame->getEntity(idCharacter);
    sf::Vector2f position = entity->Get<sf::Transformable*>("Position")->getPosition();

    graphics->correctWorldPosition(position);
    entity->Get<Velocity*>("Velocity")->reset();
    
    commands->update(dt);
    commands->onCommand(commandQueue, dt);
    
    graphics->update(dt);
    collision->update(dt);
    objectsGame->update(dt);
    
    collision->checkCollisions(graphics->getViewBounds());

}
