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
    
    
//    AnimatedSprite animatedCharacter;
//    std::vector<Animation*> animations;
//    
//    //first four positions are walking animation
//    for (int i = 0; i < 4; i++) {
//        Animation* walk = new Animation();
//        walk->setSpriteSheet(textures->get(IDTextures::Player));
//        switch (i) {
//            case DataStructureCharacter::AnimeDirections::Up:
//                walk->addFrame(sf::IntRect(32, 96, 32, 32));
//                walk->addFrame(sf::IntRect(64, 96, 32, 32));
//                walk->addFrame(sf::IntRect(32, 96, 32, 32));
//                walk->addFrame(sf::IntRect(0, 96, 32, 32));
//                break;
//            case DataStructureCharacter::AnimeDirections::Down:
//                walk->addFrame(sf::IntRect(32, 0, 32, 32));
//                walk->addFrame(sf::IntRect(64, 0, 32, 32));
//                walk->addFrame(sf::IntRect(32, 0, 32, 32));
//                walk->addFrame(sf::IntRect(0, 0, 32, 32));
//
//                break;
//            case DataStructureCharacter::AnimeDirections::Rigth:
//                walk->addFrame(sf::IntRect(32, 64, 32, 32));
//                walk->addFrame(sf::IntRect(64, 64, 32, 32));
//                walk->addFrame(sf::IntRect(32, 64, 32, 32));
//                walk->addFrame(sf::IntRect(0, 64, 32, 32));
//                break;
//            case DataStructureCharacter::AnimeDirections::Left:
//                walk->addFrame(sf::IntRect(32, 32, 32, 32));
//                walk->addFrame(sf::IntRect(64, 32, 32, 32));
//                walk->addFrame(sf::IntRect(32, 32, 32, 32));
//                walk->addFrame(sf::IntRect(0, 32, 32, 32));
//                break;
//        }
//        animations.push_back(std::move(walk));
//    }
//    animatedCharacter.play(*animations[0]);
//    animatedCharacter.setPosition(0, 0);
//    
//    
//    character->Add<AnimatedSprite>("Drawable", animatedCharacter);
    
    
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
    
    parser=IXMLParser::make_parser(TypeParser::ANIMATION);
    parser->setResources(textures);
    parser->setXML("Media/Data/Animations.xml");
    //parser->parse().animations;
    int i=1;
    StateMachine* state=new StateMachine(i);
    StateMachineAnimation* machineAnimation=new StateMachineAnimation(*state);
    machineAnimation->setAnimations(parser->parse().animations->animations);
    character->Add<StateMachineAnimation*>("Drawable", machineAnimation);
    
    { // finished may be accessed from multiple threads, protect it
        sf::Lock lock(mutex);
        completion = 100;
        finished = true;
    }
}