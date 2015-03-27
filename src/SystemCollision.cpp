/* 
 * File:   SystemCollision.cpp
 * Author: dorian
 * 
 * Created on 15 de marzo de 2015, 21:47
 */

#include "SystemCollision.h"
#include <iostream>


SystemCollision::SystemCollision(sf::FloatRect bounds) : ISystem(), tree() {
    type=TypeSystem::COLLISION;
    tree=new QuadTree(0, bounds);
}

SystemCollision::SystemCollision() : ISystem(), tree() {
    type=TypeSystem::COLLISION;
    tree=new QuadTree(0);
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
    QuadTree* subtree=tree->getNodeRegion(region);
    if(subtree==nullptr){
        subtree=tree;
    }
    std::vector<Entity*> list=std::vector<Entity*>();
    subtree->getObjects(list);
    for(std::vector<Entity*>::iterator it = list.begin(); it != list.end(); ++it) {
        Entity* entity=*(it);
        std::vector<Entity*> posibles=std::vector<Entity*>();
        subtree->retrieve(&posibles,entity);
        
        for(std::vector<Entity*>::iterator it = posibles.begin(); it != posibles.end(); ++it) {
            if(checkCollisions(entity, *(it))){
                queue.push(MessageCollision(entity->getId(), (*(it))->getId()));
                std::cout<<"Collision"<<std::endl;
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



void SystemCollision::update(sf::Time dt) {
    tree->update();


}

void SystemCollision::newWorldCollision(sf::FloatRect bounds) {
    tree->clear();
    delete tree;
    tree=new QuadTree(0, bounds);
}


void SystemCollision::clear() {
    tree->clear();
}


void SystemCollision::finalize() {
    tree->clear();
}
