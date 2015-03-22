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
#include "SystemManager.h"
#include "Context.h"

class LoadingLevel : public ParallelTask{
public:
    LoadingLevel(Levels levelToLoad, Context* context);
    virtual ~LoadingLevel();
    

    virtual void runTask();

    
private:
    Levels level;
    Level* levelToLoad;
    ResourceHolder<IDTextures,sf::Texture>* textures;
    SystemManager* systemManager;
};

#endif	/* LOADINGLEVEL_H */

