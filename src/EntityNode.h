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

/**
 * Nodo con una entidad
 */
class EntityNode : public SceneNode {
public:
    /**
     * Constructor
     * @param entity entidad del nodo
     */
    EntityNode(Entity* entity);
    virtual ~EntityNode();

    /**
     * Devuelve la entidad del nodo
     * @return entidad del nodo
     */
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
    /**
     * Entidad del nodo
     */
    Entity* entity;

protected:
    /*
     * Update the entity given a time since the last update
     * @param dt tiempo entre frame y frame
     */
    virtual void updateCurrent(sf::Time dt);
    /**
     * Actualiza la entidad/nodo en una segunda pasada
     * @param dt tiempo entre frame y frame
     */
    virtual void updateSecondPart(sf::Time dt);
};

#endif	/* ENTITYNODE_H */

