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
#include "Velocity.h"
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

bool SystemCollision::ContinuousCollisionDetection(Entity* one) {
//    if(!one->HasID("Velocity")){
//        return false;
//    }
//    
//    Collision* collision=one->Get<Collision*>("Collision");
//    QuadTree* subtree = tree->getNodeRegion(collision->getAABB());
//    if (subtree == nullptr) {
//        subtree = tree;
//    }
//    
//    Velocity* velocity=one->Get<Velocity*>("Velocity");
    return true;
    
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

void SystemCollision::updateSecondPart(sf::Time dt) {
//    tree->update();
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

void SystemCollision::correctInsidePosition(Entity* entity) {
    Collision* collision = entity->Get<Collision*>("Collision");
    sf::FloatRect viewBounds = tree->getBounds();

    sf::Vector2f position = entity->Get<Position*>("Position")->getPosition().getPosition();
    sf::FloatRect bounds = collision->getAABB();
    position.x = std::max(position.x, viewBounds.left);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - bounds.width);
    position.y = std::max(position.y, viewBounds.top);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - bounds.height);
    Position* pos = entity->Get<Position*>("Position");
    
    sf::Transformable newPosition = sf::Transformable();
    newPosition.setPosition(position.x, position.y);
    pos->setPosition(newPosition);
}

void SystemCollision::resolveCollisions() {
    while (queue.size() > 0) {
        MessageCollision collision = queue.front();
        queue.pop();

        Collision* collisionOne = collision.entityOne->Get<Collision*>("Collision");
        Collision* collisionTwo = collision.entityTwo->Get<Collision*>("Collision");

        //lo resolverá el entity
        if (collision.entityOne->HasID("Behaviour")) {
            collision.entityOne->Get<Behaviour*>("Behaviour")->behaviourFunction(collision);
        }

    }
}

