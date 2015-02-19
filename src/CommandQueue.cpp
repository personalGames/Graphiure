/* 
 * File:   CommandQueue.cpp
 * Author: dorian
 * 
 * Created on 9 de febrero de 2015, 0:13
 */

#include "CommandQueue.h"

void CommandQueue::push(const Command& command) {
    queue.push(command);
}

Command CommandQueue::pop() {
    Command command = queue.front();
    queue.pop();
    return command;
}
