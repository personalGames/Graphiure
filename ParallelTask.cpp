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
    thread.launch();
}

bool ParallelTask::isFinished() {
    sf::Lock lock(mutex);
    return finished;
}

float ParallelTask::getCompletion() {
    sf::Lock lock(mutex);
    return completion;
}

ParallelTask::~ParallelTask() {
    //something...
}
