/* 
 * File:   Entity.h
 * Author: dorian
 *
 * Created on 15 de febrero de 2015, 14:13
 */

#ifndef ENTITY_H
#define	ENTITY_H

#include <SFML/System/Time.hpp>
#include "SceneNode.h"

class Entity : public SceneNode {
public:
    Entity();
    virtual ~Entity();

    /**
     * Get the velocity of the entity
     * @return a vector x,y of floats
     */
    inline sf::Vector2f getVelocity() const {
        return velocity;
    }

    /**
     * Set the velocity of the entity
     * @param velocity vector x,y of floats
     */
    void setVelocity(sf::Vector2f velocity);

    /**
     * Set the velocity of the entity
     * @param x axis x
     * @param y axis y
     */
    void setVelocity(float x, float y);

    /**
     * Accelerate the velocity of the entity
     * @param velocity the vector x,y of floats
     */
    void accelerate(sf::Vector2f velocity);

    /**
     * Accelerate the velocity of the entity
     * @param x axis x
     * @param y axis y
     */
    void accelerate(float x, float y);

private:
    /**
     * The velocity of the game object (entity)
     */
    sf::Vector2f velocity;

protected:
    /*
     * Update the entity given a time since the last update
     */
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
};

#endif	/* ENTITY_H */

