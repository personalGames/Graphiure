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
#include "Velocity.h"
#include "Life.h"
#include "Hole.h"
#include "FactoryGameObjects.h"
#include "XMLDocument.h"

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

    
    XMLDocument document=XMLDocument("Media/Levels/level1.xml");
    //recojo el xml del nivel
    IXMLParser* parser = IXMLParser::make_parser(TypeParser::MAP);
    parser->setResources(textures);
    parser->setXML(document);

    //parseo el nivel
    parser->parse(data);
    delete parser;
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
    
    
    // leo las colisiones del mapa 
    Entity* colisionable;
    parser = IXMLParser::make_parser(TypeParser::COLLISIONS_MAP);
    parser->setXML(document);
    parser->parse(data);
    delete parser;

    
    PropertyManager parameters;
    //la posición hay que ajustarla al tamaño modificado del mapa
    //se saca el factor del mapa y se aplica
    sf::Vector2f ratio = graphics->getRatio();
    for (std::vector<StructCollision*>::iterator it = data.collisions->begin();
            it != data.collisions->end(); ++it) {
        //pillo la estructura de esta collision en concreto
        StructCollision* coli=*it;
        //guardo los datos que se necesitarán para construir el objeto
        parameters=PropertyManager();
        parameters.Add<sf::Vector2f>("Ratio", ratio);
        parameters.Add<sf::Vector2f>("Position", coli->position );
        parameters.Add<sf::VertexArray*>("Vertex", coli->vertices);
        
        //preparo el factory que creará el entity
        std::unique_ptr<GameObjects> gameObject=FactoryGameObjects::getFactory(coli->typeCollision);
        //creo el entity
        colisionable=gameObject->prepareEntity(parameters);
        
        //registro el entity y los subsistemas lo recogerán si es de su incumbencia
        objectsGame->registerEntity(colisionable);
        delete *it;
    }
    
//    Collision* coli;
    //recojo los elementos necesarios y los comunico al manejador de recursos
    
    parser = IXMLParser::make_parser(TypeParser::CHARACTER);
    document.load("Media/Data/Character.xml");
    parser->setXML(document);
    parser->setResources(textures);
    
    parser->parse(data);
    delete parser;
    
    std::unique_ptr<GameObjects> gameObject=FactoryGameObjects::getFactory("Character");
    Entity* character = gameObject->prepareEntity(*data.propertiesEntity);
    delete data.propertiesEntity;

//    Position* trans=new Position();
//    trans->setPosition(sf::Transformable());
//    trans->updatePosition(100,100);
//    character->Add<Position*>("Position", trans);
//    Velocity* vel=new Velocity();
//    vel->setMaxVelocity(200.f);
//    character->Add<Velocity*>("Velocity", vel);
//    character->Add<bool>("Commandable", true);
//    
//    Life* life= new Life(100);
//    character->Add<Life*>("Life", life);

    levelToLoad->setCharacter(character->getId());

//    parser = IXMLParser::make_parser(TypeParser::STATE_MACHINE);
//    parser->setResources(textures);
//    parser->setXML("Media/Data/StateMachines.xml");
//    parser->parse(data);
//    delete parser;
//    StateMachine* state = data.stateMachine;
//    parser = IXMLParser::make_parser(TypeParser::ANIMATION);
//    parser->setResources(textures);
//    parser->setXML("Media/Data/Animations.xml");
//    
//    StateMachineAnimation* machineAnimation = new StateMachineAnimation(*state);
//    parser->parse(data);
//    delete parser;
//    machineAnimation->setAnimations(data.animations->animations);
//    character->Add<StateMachineAnimation*>("Drawable", machineAnimation);

    {
        sf::Lock lock(mutex);
        completion = 70;
    }

    //seteo las colisiones, de momento en debug

    //a mi personaje le doy la colisión de su cuerpo
//    coli = new Collision();
//    sf::VertexArray quad(sf::Quads, 4);
//    quad[0].position = sf::Vector2f(16, 16);
//    quad[1].position = sf::Vector2f(32, 16);
//    quad[2].position = sf::Vector2f(32, 32);
//    quad[3].position = sf::Vector2f(16, 32);
//    coli->addArrayVertex(quad);
//    coli->setType(TypeCollision::DYNAMIC);
//    character->Add<Collision*>("Collision", coli);
    
    //he terminado con mi personaje, lo registro/guardo
    objectsGame->registerEntity(character);

    
    { // finished may be accessed from multiple threads, protect it
        sf::Lock lock(mutex);
        completion = 100;
        finished = true;
    }
}