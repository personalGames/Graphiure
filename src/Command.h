/* 
 * File:   Command.h
 * Author: dorian
 *
 * Created on 9 de febrero de 2015, 0:10
 */

#ifndef COMMAND_H
#define	COMMAND_H

#include <functional>
#include <cassert>
#include <SFML/System.hpp>

#include "Category.h"

class Entity;

struct Command {
    /**
     * COnstructor
     */
    Command();
    
    /**
     * variable donde guardar la función a ejecutar
     */
    std::function<void(Entity&, sf::Time) > action;
    
    unsigned int category;
};


template <typename GameObject, typename Function>
std::function<void(Entity& node, sf::Time dt) > derivedAction(Function fn) {
    return [ = ] (Entity& node, sf::Time dt){
        // Check if cast is safe
        assert(dynamic_cast<GameObject*> (&node) != nullptr);
        // Downcast node and invoke function on it
        fn(static_cast<GameObject&> (node), dt);
    };
}

#endif	/* COMMAND_H */
