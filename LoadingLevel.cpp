/* 
 * File:   LoadingLevel.cpp
 * Author: dorian
 * 
 * Created on 11 de febrero de 2015, 23:58
 */

#include "LoadingLevel.h"


LoadingLevel::LoadingLevel(Levels level, Level* levelToLoad) : ParallelTask(),
        level(level), levelToLoad(levelToLoad)  {
}

LoadingLevel::~LoadingLevel() {

}

void LoadingLevel::runTask() {
    // Dummy task - stall 10 seconds
    bool ended = false;
    
    //compruebo el nivel que tengo que cargar
    {
        sf::Lock lock(mutex);
        completion=5;
    }
    //recojo el xml del nivel
    XMLParser* parser = new XMLParser("Media/Levels/level1.xml");
    {
        sf::Lock lock(mutex);
        completion=10;
    }
    sf::sleep(sf::milliseconds(2000));
    //parseo el nivel
    StructMap* infoMap=parser->readMap();
    {
        sf::Lock lock(mutex);
        completion=35;
    }
    
    sf::sleep(sf::milliseconds(2000));
    //recojo los elementos necesarios y los comunico al manejador de recursos
    //pass the information to build the scene with all this data readed
    levelToLoad->buildScene(infoMap);
    {
        sf::Lock lock(mutex);
        completion=70;
    }
    sf::sleep(sf::milliseconds(2000));
    
    delete infoMap;
    delete parser;
    { // finished may be accessed from multiple threads, protect it
        sf::Lock lock(mutex);
        completion=100;
        finished = true;
    }
}