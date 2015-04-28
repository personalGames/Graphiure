/* 
 * File:   SystemObjectsGame.cpp
 * Author: dorian
 * 
 * Created on 22 de marzo de 2015, 19:09
 */

#include <list>

#include "SystemObjectsGame.h"

SystemObjectsGame::SystemObjectsGame(SystemManager& systemManager): ISystem(), 
        entities(), systemManager(&systemManager), messageEntities(){
    type=TypeSystem::OBJECTS;
    messageEntities=new Subject();
}

void SystemObjectsGame::destroyEntity(IdEntity id){
    Entity* getting=getEntity(id);
    if(getting!=nullptr){
        removedEntities.push_back(getting);
        getting->destroy();
    }
}

void SystemObjectsGame::finalize() {
    //elimino todas las entidades
    auto it = entities.begin();
    while (it != entities.end()){
        //elimino el objeto
        delete it->second;
        //elimino la referencia en la lista
        it=entities.erase(it);
    }
}

Entity* SystemObjectsGame::getEntity(IdEntity id) {
    Entity* result=nullptr;
    try{
        result=entities.at(id);
    }catch(std::out_of_range exception){
        std::cout<<"Error buscando entidad"<<std::endl;
    }
    return result;
}

void SystemObjectsGame::initialize() {
    //nada en especial que hacer
}

void SystemObjectsGame::registerEntity(Entity* entity) {
    if(entities.find(entity->getId())==entities.end()){
        entity->Add<Subject*>("messageEntities", messageEntities);
        newEntity(entity);
    }
}


void SystemObjectsGame::newEntity(Entity* entity) {
    entities[entity->getId()]=entity;
    //aviso a los demás subsistemas de que hay nueva entidad por si quieren 
    //vigilarlo
    systemManager->registerEntity(entity);
}


void SystemObjectsGame::update(sf::Time dt) {
    if(removedEntities.size()>0){
        auto it = removedEntities.begin();
        while (it != removedEntities.end()){
            //aviso a los subsistemas que este id ya no está
            systemManager->removeEntity(*it);
            entities.erase((*it)->getId());
            it=removedEntities.erase(it);
        }
    }
}


SystemObjectsGame::~SystemObjectsGame() {
    finalize();
}
