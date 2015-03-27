/* 
 * File:   LoadingLevel.cpp
 * Author: dorian
 * 
 * Created on 11 de febrero de 2015, 23:58
 */

#include "LoadingLevel.h"
#include "Entity.h"
#include "AnimatedSprite.h"
#include "IXMLParser.h"
#include "StateMachineAnimation.h"
#include "SystemObjectsGame.h"
#include "SystemGraphic.h"

LoadingLevel::LoadingLevel(Levels level, Context* context)
: ParallelTask(), level(level), context(context) {
    levelToLoad=context->actualLevel;
    this->textures = context->textures;
    this->systemManager=context->systemManager;
}

LoadingLevel::~LoadingLevel() {

}

void LoadingLevel::runTask() {
    //compruebo el nivel que tengo que cargar
    {
        sf::Lock lock(mutex);
        completion = 5;
    }

    DataUnion data = DataUnion();
    
    
    //preparo los sistemas que necesito
    SystemCollision* collision = static_cast<SystemCollision*>(systemManager->getSystem(TypeSystem::COLLISION));
    SystemGraphic* graphics=static_cast<SystemGraphic*>(systemManager->getSystem(TypeSystem::GRAPHIC));
    //y por último el sistema de objetos
    SystemObjectsGame* objectsGame= static_cast<SystemObjectsGame*>(systemManager->getSystem(TypeSystem::OBJECTS));

    
    
    
    //recojo el xml del nivel
    IXMLParser* parser = IXMLParser::make_parser(TypeParser::MAP);
    parser->setResources(textures);
    parser->setXML("Media/Levels/level1.xml");

    //parseo el nivel
    parser->parse(data);
    StructMap* infoMap = data.map;
    {
        sf::Lock lock(mutex);
        completion = 10;
    }
    
    
    

    //pass the information to build the scene with all this data readed
    graphics->newScene(infoMap);
    collision->newWorldCollision(graphics->getBounds());
    {
        sf::Lock lock(mutex);
        completion = 35;
    }

    delete infoMap;
    delete parser;
    
    
    // leo las colisiones del mapa
    Collision* coli;
    Entity* colisionable;
    parser = IXMLParser::make_parser(TypeParser::COLLISIONS);
    parser->setXML("Media/Levels/level1.xml");
    parser->parse(data);

    //la posición hay que ajustarla al tamaño modificado del mapa
    //se saca el factor del mapa y se aplica
    sf::Vector2f ratio = graphics->getRatio();
    for (std::vector<Collision*>::iterator it = data.collisions->begin();
            it != data.collisions->end(); ++it) {
        coli=*it;
        coli->applyRatio(ratio);
        colisionable=new Entity();
        colisionable->Add<sf::Transformable*>("Position", coli->getTransform());
        colisionable->Add<Collision*>("Collision", coli);
        //registro el entity y los subsistemas lo recogerán si es de su incumbencia
        objectsGame->registerEntity(colisionable);
    }
    

    
    
    
    
    
    
    //recojo los elementos necesarios y los comunico al manejador de recursos
    Entity* character = new Entity(Category::CHARACTER);

    sf::Transformable* trans = new sf::Transformable();
    trans->setPosition(100, 100);
    character->Add<sf::Transformable*>("Position", trans);
    character->Add<sf::Vector2f>("Velocity", sf::Vector2f(0, 0));
    character->Add<float>("MaxVelocity", 200.f);
    character->Add<bool>("Commandable", true);

    levelToLoad->setCharacter(character->getId());

    parser = IXMLParser::make_parser(TypeParser::STATE_MACHINE);
    parser->setResources(textures);
    parser->setXML("Media/Data/StateMachines.xml");
    parser->parse(data);
    StateMachine* state = data.stateMachine;
    delete parser;
    parser = IXMLParser::make_parser(TypeParser::ANIMATION);
    parser->setResources(textures);
    parser->setXML("Media/Data/Animations.xml");

    StateMachineAnimation* machineAnimation = new StateMachineAnimation(*state);
    parser->parse(data);
    machineAnimation->setAnimations(data.animations->animations);
    character->Add<StateMachineAnimation*>("Drawable", machineAnimation);
    delete parser;
    {
        sf::Lock lock(mutex);
        completion = 70;
    }

    //seteo las colisiones, de momento en debug

    //a mi personaje le doy la colisión de su cuerpo
    coli = new Collision();
    sf::VertexArray quad(sf::Quads, 4);
    quad[0].position = sf::Vector2f(0, 0);
    quad[1].position = sf::Vector2f(32, 0);
    quad[2].position = sf::Vector2f(32, 32);
    quad[3].position = sf::Vector2f(0, 32);
    coli->addArrayVertex(quad);
    character->Add<Collision*>("Collision", coli);
    
    //he terminado con mi personaje, lo registro/guardo
    objectsGame->registerEntity(character);

    
   
    
    
    { // finished may be accessed from multiple threads, protect it
        sf::Lock lock(mutex);
        completion = 100;
        finished = true;
    }
}