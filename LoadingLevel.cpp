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
    //recojo el xml del nivel
    //parseo el nivel
    //recojo los elementos necesarios y los comunico al manejador de recursos
    //pass the information to build the scene with all this data readed
    levelToLoad->buildScene();
    while (!ended) {
        sf::Lock lock(mutex); // Protect the  completion
        
        ended=true;
    }

    
    
    { // finished may be accessed from multiple threads, protect it
        sf::Lock lock(mutex);
        finished = true;
    }
}