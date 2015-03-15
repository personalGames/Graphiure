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

namespace DataStructureCharacter {
    enum AnimeDirections {
        Up = 0,
        Down = 1,
        Rigth,
        Left,
        EnumCount
    };
};

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
    //XMLParser* parser = new XMLParser("Media/Levels/level1.xml");
    {
        sf::Lock lock(mutex);
        completion = 10;
    }
//    sf::sleep(sf::milliseconds(2000));
    //parseo el nivel
    StructMap* infoMap = parser->parse().map;
    {
        sf::Lock lock(mutex);
        completion = 35;
    }

    //sf::sleep(sf::milliseconds(2000));
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
        completion = 70;
    }
    //sf::sleep(sf::milliseconds(300));

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
    
    { // finished may be accessed from multiple threads, protect it
        sf::Lock lock(mutex);
        completion = 100;
        finished = true;
    }
}