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
    virtual void updateCurrent(sf::Time dt);
    
    virtual void updateSecondPart(sf::Time dt);
    

//    virtual void onCommand(const Command& command, sf::Time delta);

};

#endif	/* ENTITYNODE_H */

