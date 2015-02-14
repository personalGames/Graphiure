/* 
 * File:   ParallelTask.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 17:48
 */

#ifndef PARALLELTASK_H
#define	PARALLELTASK_H

#include <SFML/System.hpp>

class ParallelTask {
public:
    ParallelTask();
    void execute();
    bool isFinished();
    float getCompletion();
    
    virtual ~ParallelTask();

    virtual void runTask()=0;
protected:
    sf::Thread thread;
    bool finished;
    sf::Mutex mutex;
    /**
     * Number between 0 and 1 (percentaje of completion)
     */
    int completion;

};

#endif	/* PARALLELTASK_H */

