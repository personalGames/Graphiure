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

LoadingLevel::LoadingLevel(Levels level, Level* levelToLoad, ResourceHolder<IDTextures,sf::Texture>* textures) : ParallelTask(),
level(level), levelToLoad(levelToLoad){
    this->textures=textures;
}

LoadingLevel::~LoadingLevel() {

}

void LoadingLevel::runTask() {
    //compruebo el nivel que tengo que cargar
    {
        sf::Lock lock(mutex);
        completion = 5;
    }
    //recojo el xml del nivel
    IXMLParser* parser=IXMLParser::make_parser(TypeParser::MAP);
    parser->setResources(textures);
    parser->setXML("Media/Levels/level1.xml");
    
    //parseo el nivel
    StructMap* infoMap = parser->parse().map;
    {
        sf::Lock lock(mutex);
        completion = 10;
    }

    //recojo los elementos necesarios y los comunico al manejador de recursos
    Entity* character=new Entity();
    
    sf::Transformable trans=sf::Transformable();
    trans.setPosition(0,0);
    character->Add<sf::Transformable>("Position",trans);
    character->Add<sf::Vector2f>("Velocity",sf::Vector2f(0,0));
    character->Add<float>("MaxVelocity",200.f);
    
    //pass the information to build the scene with all this data readed
    levelToLoad->buildScene(infoMap, character);
    {
        sf::Lock lock(mutex);
        completion = 35;
    }

    delete infoMap;
    delete parser;
    
    parser=IXMLParser::make_parser(TypeParser::STATE_MACHINE);
    parser->setResources(textures);
    parser->setXML("Media/Data/StateMachines.xml");
    StateMachine* state=parser->parse().stateMachine;
    delete parser;
    
    parser=IXMLParser::make_parser(TypeParser::ANIMATION);
    parser->setResources(textures);
    parser->setXML("Media/Data/Animations.xml");
    
    StateMachineAnimation* machineAnimation=new StateMachineAnimation(*state);
    machineAnimation->setAnimations(parser->parse().animations->animations);
    character->Add<StateMachineAnimation*>("Drawable", machineAnimation);
    delete parser;
    {
        sf::Lock lock(mutex);
        completion = 70;
    }
    
    
    //seteo las colisiones, de momento en debug
    //las seteo a mano directamente
    SystemCollision* collision=new SystemCollision(levelToLoad->getBounds());
    
    //a mi personaje le doy la colisión de su cuerpo
    Collision* coli=new Collision();
    sf::VertexArray quad(sf::Quads, 4);
    quad[0].position = sf::Vector2f(0, 0);
    quad[1].position = sf::Vector2f(32, 0);
    quad[2].position = sf::Vector2f(32, 32);
    quad[3].position = sf::Vector2f(0, 32);
    coli->addArrayVertex(quad);
    character->Add<Collision*>("Collision", coli);
    
    // y una colisión cualquiera para probar
    Entity* arg=new Entity();
    sf::Transformable tr=sf::Transformable();
    tr.setPosition(639, 296);
    arg->Add<sf::Transformable>("Position",tr);
    
    coli=new Collision();
    sf::VertexArray quad2(sf::Quads, 4);
    quad2[0].position = sf::Vector2f(0,0);
    quad2[1].position = sf::Vector2f(32, 0);
    quad2[2].position = sf::Vector2f(32, 32);
    quad2[3].position = sf::Vector2f(0, 32);
    coli->addArrayVertex(quad2);
    arg->Add<Collision*>("Collision", coli);
    
    //meto mi personaje
    collision->addCollisionable(character);
    //y al colisionable
    collision->addCollisionable(arg);
    
    levelToLoad->setSystemCollision(collision);
    
    { // finished may be accessed from multiple threads, protect it
        sf::Lock lock(mutex);
        completion = 100;
        finished = true;
    }
}