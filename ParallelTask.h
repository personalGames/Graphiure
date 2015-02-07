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

private:
    void runTask();

    sf::Thread thread;
    bool finished;
    sf::Clock elapsedTime;
    sf::Mutex mutex;

};

#endif	/* PARALLELTASK_H */

