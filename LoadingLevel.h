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

class LoadingLevel : public ParallelTask{
public:
    LoadingLevel(Levels levelToLoad, Level* load);
    virtual ~LoadingLevel();
    

    virtual void runTask();

    
private:
    Levels level;
    Level* levelToLoad;
};

#endif	/* LOADINGLEVEL_H */

