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
    //constructor of the structure
    Command();
    
    /**
     * This is a method/variable where store an action an execute it when call action
     * from struct command.
     * Example: 
     * .action = derivedAction<Avion>(AircraftMover(-1, 0));
     * 
     * //en clase avion
     * Command mFireCommand;
     * mFireCommand.action = [this, &textures] (SceneNode& node, sf::Time) {
        createBullets(node, textures); --> método del objeto a ejecutar
       };
     * 
     * //en clase emisor node
     * // Find particle node with the same type as emitter node
        auto finder = [this] (ParticleNode& container, sf::Time) {
            if (container.getParticleType() == mType)
                mParticleSystem = &container;
        };
     * command.action = derivedAction<ParticleNode>(finder);
     * 
     * Y ejecutan como
     * command.action(*this, delta); (el this es el nodo involucrado, creo)
     */
    std::function<void(Entity&, sf::Time) > action;
    
    unsigned int category;
};

//TODO: habrá que adaptar el node a entity para no limitar los comandos a los nodos
//aunque es posible que no haga falta, en principio todo objeto para comandos va a
//estar en el scene graph
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
