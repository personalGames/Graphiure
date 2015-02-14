/* 
 * File:   ParallelTask.cpp
 * Author: dorian
 * 
 * Created on 13 de diciembre de 2014, 17:48
 */

#include "ParallelTask.h"

ParallelTask::ParallelTask(): thread(&ParallelTask::runTask, this), finished(false), completion(0) {
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
    return completion*0.01;
}

ParallelTask::~ParallelTask() {
    //something...
}
