/* 
 * File:   CommandQueue.h
 * Author: dorian
 *
 * Created on 9 de febrero de 2015, 0:13
 */

#ifndef COMMANDQUEUE_H
#define	COMMANDQUEUE_H

#include <queue>
#include "Command.h"

/**
 * Pila para los comandos
 */
class CommandQueue {
public:
    /**
     * Add command
     * @param command
     */
    void push(const Command& command);
    /**
     * Pop command
     * @return the command
     */
    Command pop();

    /**
     * is empty
     * @return 
     */
    inline bool isEmpty() const {
        return queue.empty();
    }

private:
    //queue
    std::queue<Command> queue;

};

#endif	/* COMMANDQUEUE_H */

