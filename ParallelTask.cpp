/* 
 * File:   ParallelTask.cpp
 * Author: dorian
 * 
 * Created on 13 de diciembre de 2014, 17:48
 */

#include "ParallelTask.h"

ParallelTask::ParallelTask(): thread(&ParallelTask::runTask, this), finished(false) {
}

void ParallelTask::execute() {
    finished = false;
    elapsedTime.restart();
    thread.launch();
}

bool ParallelTask::isFinished() {
    sf::Lock lock(mutex);
    return finished;
}

float ParallelTask::getCompletion() {
    sf::Lock lock(mutex);

    // 100% at 10 seconds of elapsed time
    return elapsedTime.getElapsedTime().asSeconds() / 10.f;
}

void ParallelTask::runTask() {
    // Dummy task - stall 10 seconds
    bool ended = false;
    while (!ended) {
        sf::Lock lock(mutex); // Protect the clock 
        if (elapsedTime.getElapsedTime().asSeconds() >= 10.f)
            ended = true;
    }

    
    { // mFinished may be accessed from multiple threads, protect it
        sf::Lock lock(mutex);
        finished = true;
    }
}