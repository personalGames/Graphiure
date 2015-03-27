/* 
 * File:   EntityNode.h
 * Author: dorian
 *
 * Created on 4 de marzo de 2015, 12:22
 */

#ifndef ENTITYNODE_H
#define	ENTITYNODE_H

#include "Entity.h"
#include "SceneNode.h"
#include "PropertyManager.h"
#include "Actions.h"
#include <SFML/System/Vector2.hpp>

class EntityNode : public SceneNode {
public:
    EntityNode(Entity* entity);
    virtual ~EntityNode();

    Entity* getEntity() const {
        return entity;
    }

    /**
     * Get the velocity of the entity
     * @return a vector x,y of floats
     */
    sf::Vector2f getVelocity() const;

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
    
    void adaptVelocity();

    virtual unsigned int getCategory() const;

    float getMaxSpeed() const;

    void updateAnimation(Actions action);

    /**
     * Inherit from SceneNode, draw the entity
     * @param target
     * @param states
     */
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    Entity* entity;

protected:
    /*
     * Update the entity given a time since the last update
     */
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
    

//    virtual void onCommand(const Command& command, sf::Time delta);

};

#endif	/* ENTITYNODE_H */

