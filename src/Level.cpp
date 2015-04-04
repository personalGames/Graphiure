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
    
    movement = static_cast<SystemMovement*>
            (systemManager.getSystem(TypeSystem::MOVEMENT));
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
    //get the entity/character
    Entity* entity = objectsGame->getEntity(idCharacter);
    //reset position character
    collision->correctInsidePosition(entity);
    //reset velocity
    entity->Get<Velocity*>("Velocity")->reset();
    
    
    //update all input
    commands->update(dt);
    commands->onCommand(commandQueue, dt);
    
    //simulate movements
    movement->update(dt);
    //check CCD, the tree has update with the aabbswept
    collision->update(dt);
    //check CCD
//    collision->checkCollisions(graphics->getViewBounds());
    
    //update movements definitive
//    movement->updateSecondPart(dt);
    
    //update tree collisions definitive and checks collisions
//    collision->updateSecondPart(dt);
    
    //check the collisions
    collision->checkCollisions(graphics->getViewBounds());
    //resolve the collisions (separate bodies and generate the commands
    //for next frame)
    collision->resolveCollisions();
    
    //update the scene (update the animations)
    graphics->update(dt);
    //graphics second update, only set positions (changed by collisions) and sort the tree by y
    //graphics->updateSecondPart(dt);
    
    
    //update the world with the final position of character
    sf::Vector2f position = entity->Get<Position*>("Position")->getPosition().getPosition();
    graphics->correctWorldPosition(position);
    
    //update objects in general (delete dead objects)
    objectsGame->update(dt);
}
