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

LoadingLevel::LoadingLevel(Levels level, Level* levelToLoad, ResourceHolder<IDTextures, sf::Texture>* textures)
: ParallelTask(), level(level), levelToLoad(levelToLoad) {
    this->textures = textures;
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
    levelToLoad->buildScene(infoMap);
    {
        sf::Lock lock(mutex);
        completion = 35;
    }

    delete infoMap;
    delete parser;

    //recojo los elementos necesarios y los comunico al manejador de recursos
    Entity* character = new Entity();

    sf::Transformable* trans = new sf::Transformable();
    trans->setPosition(100, 100);
    character->Add<sf::Transformable*>("Position", trans);
    character->Add<sf::Vector2f>("Velocity", sf::Vector2f(0, 0));
    character->Add<float>("MaxVelocity", 200.f);

    levelToLoad->setCharacter(character);

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
    //las seteo a mano directamente
    SystemCollision* collision = new SystemCollision(levelToLoad->getBounds());

    //a mi personaje le doy la colisión de su cuerpo
    Collision* coli = new Collision();
    sf::VertexArray quad(sf::Quads, 4);
    quad[0].position = sf::Vector2f(0, 0);
    quad[1].position = sf::Vector2f(32, 0);
    quad[2].position = sf::Vector2f(32, 32);
    quad[3].position = sf::Vector2f(0, 32);
    coli->addArrayVertex(quad);
    character->Add<Collision*>("Collision", coli);



    // y una colisión cualquiera para probar
    Entity* colisionable;
    parser = IXMLParser::make_parser(TypeParser::COLLISIONS);
    parser->setXML("Media/Levels/level1.xml");
    parser->parse(data);

    //la posición hay que ajustarla al tamaño modificado del mapa
    //se saca el factor del mapa y se aplica
    sf::Vector2f ratio = levelToLoad->getRatio();
    for (std::vector<Collision*>::iterator it = data.collisions->begin();
            it != data.collisions->end(); ++it) {
        coli=*it;
        coli->applyRatio(ratio);
        colisionable=new Entity();
        colisionable->Add<sf::Transformable*>("Position", coli->getTransform());
        colisionable->Add<Collision*>("Collision", coli);
        collision->addCollisionable(colisionable);
    }
    
    for(int i=0; i< 5; ++i){
        colisionable=new Entity();
        colisionable->Add<sf::Transformable*>("Position", coli->getTransform());
        colisionable->Add<Collision*>("Collision", coli);
        collision->addCollisionable(colisionable);
    }
    
    //meto mi personaje
    collision->addCollisionable(character);
    //y al colisionable
    

    levelToLoad->setSystemCollision(collision);

    { // finished may be accessed from multiple threads, protect it
        sf::Lock lock(mutex);
        completion = 100;
        finished = true;
    }
}