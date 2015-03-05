/* 
 * File:   LoadingLevel.cpp
 * Author: dorian
 * 
 * Created on 11 de febrero de 2015, 23:58
 */

#include "LoadingLevel.h"
#include "Entity2.h"

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
    XMLParser* parser = new XMLParser("Media/Levels/level1.xml");
    {
        sf::Lock lock(mutex);
        completion = 10;
    }
//    sf::sleep(sf::milliseconds(2000));
    //parseo el nivel
    StructMap* infoMap = parser->readMap();
    {
        sf::Lock lock(mutex);
        completion = 35;
    }

    //sf::sleep(sf::milliseconds(2000));
    //recojo los elementos necesarios y los comunico al manejador de recursos
    //Character* character=new Character(*textures);
    Entity2* character=new Entity2();
    
    
    AnimatedSprite animatedCharacter;
    std::vector<Animation*> animations;
    
    //first four positions are walking animation
    for (int i = 0; i < 4; i++) {
        Animation* walk = new Animation();
        walk->setSpriteSheet(textures->get(IDTextures::Player));
        switch (i) {
            case DataStructureCharacter::AnimeDirections::Up:
                walk->addFrame(sf::IntRect(32, 96, 32, 32));
                walk->addFrame(sf::IntRect(64, 96, 32, 32));
                walk->addFrame(sf::IntRect(32, 96, 32, 32));
                walk->addFrame(sf::IntRect(0, 96, 32, 32));
                break;
            case DataStructureCharacter::AnimeDirections::Down:
                walk->addFrame(sf::IntRect(32, 0, 32, 32));
                walk->addFrame(sf::IntRect(64, 0, 32, 32));
                walk->addFrame(sf::IntRect(32, 0, 32, 32));
                walk->addFrame(sf::IntRect(0, 0, 32, 32));

                break;
            case DataStructureCharacter::AnimeDirections::Rigth:
                walk->addFrame(sf::IntRect(32, 64, 32, 32));
                walk->addFrame(sf::IntRect(64, 64, 32, 32));
                walk->addFrame(sf::IntRect(32, 64, 32, 32));
                walk->addFrame(sf::IntRect(0, 64, 32, 32));
                break;
            case DataStructureCharacter::AnimeDirections::Left:
                walk->addFrame(sf::IntRect(32, 32, 32, 32));
                walk->addFrame(sf::IntRect(64, 32, 32, 32));
                walk->addFrame(sf::IntRect(32, 32, 32, 32));
                walk->addFrame(sf::IntRect(0, 32, 32, 32));
                break;
        }
        animations.push_back(std::move(walk));
    }
    animatedCharacter.play(*animations[0]);
    animatedCharacter.setPosition(0, 0);
    
    
    character->Add<AnimatedSprite>("Drawable", animatedCharacter);
    character->Add<sf::Vector2f>("Position",sf::Vector2f(0,0));
    character->Add<sf::Vector2f>("Velocity",sf::Vector2f(0,0));
    
    //pass the information to build the scene with all this data readed
    levelToLoad->buildScene(infoMap, character);
    {
        sf::Lock lock(mutex);
        completion = 70;
    }
    //sf::sleep(sf::milliseconds(300));

    delete infoMap;
    delete parser;
    { // finished may be accessed from multiple threads, protect it
        sf::Lock lock(mutex);
        completion = 100;
        finished = true;
    }
}