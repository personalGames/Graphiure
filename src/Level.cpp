/* 
 * File:   Level.cpp
 * Author: dorian
 * 
 * Created on 9 de febrero de 2015, 0:08
 */

#include "Level.h"
#include <iostream>

Level::Level(SystemManager& systemManager) :
Observer(), systemManager(&systemManager), state(nullptr) {

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

    setSubject(objectsGame->getMessageEntities());
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

    if (state != nullptr) {
        state->draw();
    }
}

bool Level::handleEvent(const sf::Event& event) {
    if (state != nullptr) {
        state->handleEvent(event);
    } else {
        player->handleEvent(event, commandQueue);
    }
    return true;
}

void Level::update(sf::Time dt) {
    if(state!=nullptr && state->isEnded()){
        delete state;
        state=nullptr;
    }
    //get the entity/character
    Entity* entity = objectsGame->getEntity(idCharacter);
    if (state == nullptr) {
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

        //check the collisions
        collision->checkCollisions(graphics->getViewBounds());
        //resolve the collisions (separate bodies and generate the commands
        //for next frame)
        collision->resolveCollisions();
    } else {
        state->update(dt);
    }

    //update the scene (update the animations)
    graphics->update(dt);
    //graphics second update, only set positions (changed by collisions and anothers) and sort the tree by y
    graphics->updateSecondPart(dt);


    //update the world with the final position of character
    sf::Vector2f position = entity->Get<Position*>("Position")->getPosition().getPosition();
    graphics->correctWorldPosition(position);

    //update objects in general (delete dead objects)
    objectsGame->update(dt);

    if (state == nullptr) {
        player->handleRealtimeInput(commandQueue);
    }
}

void Level::update() {
    Message message = getSubject()->getMessage();
    GameStates stateGame = message.getState();
    switch (stateGame) {
        case GameStates::GAMING:
            break;
        case GameStates::CONVERSATION:
            state = (SubStateGame*)new ConversationState(message.getIdEntity(), systemManager);
            break;
        case GameStates::INVENTORY:
            break;
    }
    //read the messages from the entities and react
    //switch type of message
    //if talk, change state to talk
    //if inventory, change state to inventory
}
