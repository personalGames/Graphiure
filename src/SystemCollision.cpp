/* 
 * File:   SystemCollision.cpp
 * Author: dorian
 * 
 * Created on 15 de marzo de 2015, 21:47
 */

#include "SystemCollision.h"

SystemCollision::SystemCollision(sf::FloatRect bounds) : tree(0, bounds) {
}

SystemCollision::~SystemCollision() {
}

void SystemCollision::addCollisionable(Entity* entity) {
    if (entity->HasID("Collision") && entity->HasID("Position")) {
        tree.insert(entity);
    }
}

void SystemCollision::checkCollisions() {
    
}


void SystemCollision::update() {
    tree.update();
}