/* 
 * File:   SystemCollision.cpp
 * Author: dorian
 * 
 * Created on 15 de marzo de 2015, 21:47
 */

#include "SystemCollision.h"
#include <iostream>


SystemCollision::SystemCollision(sf::FloatRect bounds) : tree(0, bounds) {
}

SystemCollision::~SystemCollision() {
}

void SystemCollision::addCollisionable(Entity* entity) {
    if (entity->HasID("Collision") && entity->HasID("Position")) {
        tree.insert(entity);
    }
}

void SystemCollision::checkCollisions(sf::FloatRect region) {
    QuadTree* subtree=tree.getNodeRegion(region);
    if(subtree==nullptr){
        subtree=&tree;
    }
    std::vector<Entity*> list=std::vector<Entity*>();
    subtree->getObjects(list);
    std::cout<<list.size()<<std::endl;
    for(std::vector<Entity*>::iterator it = list.begin(); it != list.end(); ++it) {
        Entity* entity=*(it);
        std::vector<Entity*> posibles=std::vector<Entity*>();
        subtree->retrieve(&posibles,entity);
        
        for(std::vector<Entity*>::iterator it = posibles.begin(); it != posibles.end(); ++it) {
            if(checkCollisions(entity, *(it))){
                queue.push(MessageCollision(entity->getId(), (*(it))->getId()));
//                std::cout<<"Collision"<<std::endl;
            }
        }
    }
}

bool SystemCollision::checkCollisions(Entity* one, Entity* another) {
    if(one->getId()==another->getId()){
        return false;
    }
    Collision* oneCol=one->Get<Collision*>("Collision");
    Collision* anotherCol=another->Get<Collision*>("Collision");
    
    return oneCol->collision(anotherCol);
}



void SystemCollision::update() {
    tree.update();
}