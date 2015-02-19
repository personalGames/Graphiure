/* 
 * File:   LoadingLevel.h
 * Author: dorian
 *
 * Created on 11 de febrero de 2015, 23:58
 */

#ifndef LOADINGLEVEL_H
#define	LOADINGLEVEL_H

#include "ParallelTask.h"
#include "Levels.h"
#include "Level.h"
#include "ResourceHolder.h"
#include "IDTextures.h"
#include "Character.h"

class LoadingLevel : public ParallelTask{
public:
    LoadingLevel(Levels levelToLoad, Level* load, 
            ResourceHolder<IDTextures,sf::Texture>* textures);
    virtual ~LoadingLevel();
    

    virtual void runTask();

    
private:
    Levels level;
    Level* levelToLoad;
    ResourceHolder<IDTextures,sf::Texture>* textures;
};

#endif	/* LOADINGLEVEL_H */

