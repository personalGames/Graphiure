/* 
 * File:   SystemCollision.cpp
 * Author: dorian
 * 
 * Created on 15 de marzo de 2015, 21:47
 */

#include "SystemCollision.h"
#include <iostream>
#include "Collision.h"

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
    std::vector<Entity*> list=std::vector<Entity*>();
    tree.getObjects(list);
    
    for(std::vector<Entity*>::iterator it = list.begin(); it != list.end(); ++it) {
        Entity* entity=*(it);
        std::vector<Entity*> posibles=std::vector<Entity*>();
        tree.retrieve(&posibles,entity);
        
        for(std::vector<Entity*>::iterator it = posibles.begin(); it != posibles.end(); ++it) {
            if(checkCollisions(entity, *(it))){
                std::cout<<"Collision"<<std::endl;
            }
        }
    }
}

bool SystemCollision::checkCollisions(Entity* one, Entity* another) {
    if(one==another){
        return false;
    }
    Collision* oneCol=one->Get<Collision*>("Collision");
    Collision* anotherCol=another->Get<Collision*>("Collision");
    
    return oneCol->collision(anotherCol);
}



void SystemCollision::update() {
    tree.update();
}