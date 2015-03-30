/* 
 * File:   SystemCollision.cpp
 * Author: dorian
 * 
 * Created on 15 de marzo de 2015, 21:47
 */

#include "SystemCollision.h"
#include "Position.h"
#include "ActionStack.h"
#include "Behaviour.h"
#include <iostream>

SystemCollision::SystemCollision(sf::FloatRect bounds) : ISystem(), tree() {
    type = TypeSystem::COLLISION;
    tree = new QuadTree(0, bounds);
}

SystemCollision::SystemCollision() : ISystem(), tree() {
    type = TypeSystem::COLLISION;
    tree = new QuadTree(0);
}

SystemCollision::~SystemCollision() {
}

void SystemCollision::registerEntity(Entity* entity) {
    if (entity->HasID("Collision") && entity->HasID("Position")) {
        tree->insert(entity);
    }
}

void SystemCollision::removedEntity(Entity* entity) {
    tree->remove(entity);
}

void SystemCollision::checkCollisions(sf::FloatRect region) {
    QuadTree* subtree = tree->getNodeRegion(region);
    if (subtree == nullptr) {
        subtree = tree;
    }
    std::vector<Entity*> list = std::vector<Entity*>();
    subtree->getObjects(list);
    for (std::vector<Entity*>::iterator it = list.begin(); it != list.end(); ++it) {
        Entity* entity = *(it);
        std::vector<Entity*> posibles = std::vector<Entity*>();
        subtree->retrieve(&posibles, entity);

        for (std::vector<Entity*>::iterator it = posibles.begin(); it != posibles.end(); ++it) {
            if (checkCollisions(entity, *(it))) {
                queue.push(MessageCollision(entity, *(it)));
            }
        }
    }
}

bool SystemCollision::checkCollisions(Entity* one, Entity* another) {
    if (one->getId() == another->getId()) {
        return false;
    }
    Collision* oneCol = one->Get<Collision*>("Collision");
    Collision* anotherCol = another->Get<Collision*>("Collision");

    return oneCol->collision(anotherCol) > 0;
}

void SystemCollision::update(sf::Time dt) {
    tree->update();
}

void SystemCollision::newWorldCollision(sf::FloatRect bounds) {
    tree->clear();
    delete tree;
    tree = new QuadTree(0, bounds);
}

void SystemCollision::clear() {
    tree->clear();
}

void SystemCollision::finalize() {
    tree->clear();
}

void SystemCollision::resolveCollisions() {
    while (queue.size() > 0) {
        MessageCollision collision = queue.front();
        queue.pop();
        
        Collision* collisionOne = collision.entityOne->Get<Collision*>("Collision");
        if ((collisionOne->getType() == TypeCollision::STATIC) || (collisionOne->getType()==TypeCollision::KINEMATIC)) {
            //nada que hacer, empuja al otro para evitar colision
            
            Collision* collisionTwo = collision.entityTwo->Get<Collision*>("Collision");
            Position* positionTwo = collision.entityTwo->Get<Position*>("Position");
            sf::Vector2f separation = collisionOne->normalSeparation(collisionTwo);
            
            positionTwo->updatePosition(separation.x, separation.y);
            
        }else{
            //lo resolverá el entity
            if(collision.entityOne->HasID("Behaviour")){
                collision.entityOne->Get<Behaviour*>("Behaviour")->behaviourFunction(collision);
            }
        }
    }
}

