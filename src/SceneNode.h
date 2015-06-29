/* 
 * File:   SceneNode.h
 * Author: dorian
 *
 * Created on 12 de diciembre de 2014, 23:09
 */

#ifndef SCENENODE_H
#define	SCENENODE_H

#include <vector>
#include <set>
#include <algorithm> //for lambda find_if
#include <functional> // for lambda std::mem_fn(&SceneNode::isMarkedForRemoval)
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include "Command.h"
#include <utility>
#include <cmath>
#include "CommandQueue.h"
#include "Utilities.h"
#include <iostream>

/**
 * Defines a node from a scene graph
 * Can be drawed, has a position and orientation and can't be cloned
 */
class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
    /**
     * Constructor
     */
    SceneNode();
    /**
     * Constructor especificando la categoría
     * @param category categoría del nodo
     */
    SceneNode(Category category);

    virtual ~SceneNode();

    typedef std::pair<SceneNode*, SceneNode*> Pair;

    /**
     * Add a node to this node
     * @param child the child
     */
    void addChild(SceneNode* child);

    /**
     * Remove the given node to this node
     * @param node the child to remove
     * @return the removed node
     */
    SceneNode* removeChild(const SceneNode& node);

    
    void remove();
    
    /**
     * Get the absolute transform (position/rotation and scale) of the node
     * @return the absolute transform
     */
    sf::Transform getWorldTransform() const;

    /**
     * Get the relative position of the node
     * @return a vector x,y of floats
     */
    sf::Vector2f getWorldPosition() const;


    void update(sf::Time dt);
    virtual void updateSecondPart(sf::Time dt);

    /**
     * Get the category of this node.
     * @return the category of the node
     */
    virtual unsigned int getCategory() const;

    /**
     * Elimina los nodos marcados
     */
    void removeWrecks();
    /*
     * Devuelve si el nodo es marcado para eliminar 
     * @return true si esta destruido
     */
    virtual bool isMarkedForRemoval() const;
    /**
     * Devuelve si el nodo está destruido
     * @return true si esta destruido
     */
    virtual bool isDestroyed() const;

    /**
     * Devuelve el desplazamiento en el eje X, si lo hubiera, a efectos de ordenar
     * y dar sensación de profundidad
     * @return el offset en el eje x
     */
    inline float getXOffset() const {
        return xOffset;
    }

    /**
     * Devuelve el desplazamiento en el eje Y, si lo hubiera, a efectos de ordenar
     * y dar sensación de profundidad
     * @return el offset en el eje y
     */
    inline float getYOffset() const {
        return yOffset;
    }

    /**
     * Setea el offset en el eje x
     * @param xOffset offset en el eje x
     */
    void setXOffset(float xOffset) {
        this->xOffset = xOffset;
    }

    /**
     * Setea el offset en el eje y
     * @param xOffset offset en el eje y
     */
    void setYOffset(float yOffset) {
        this->yOffset = yOffset;
    }



protected:
    /**
     * Desplazamiento en el eje x
     */
    float xOffset;
    /**
     * Desplazamiento en el eje y
     */
    float yOffset;
    /**
     * Vector of children nodes
     */
    std::vector<SceneNode*> children;


private:

    /**
     * The parent of this node
     */
    SceneNode* parent;
    /**
     * Categoría del nodo
     */
    Category defaultCategory;

    /**
     * Update the node with the time since last update
     * @param delta
     */
    virtual void updateCurrent(sf::Time delta);

    /**
     * Update the children
     * @param delta
     */
    void updateChildren(sf::Time delta);

    /**
     * Inherit from drawable. Draw the node. Is overriden by  concrete class
     * as an example, aircraft, spriteNode...
     * @param target
     * @param states
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /**
     * Draw the actual state of the node
     * @param target
     * @param states
     */
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    /**
     * Draw children
     * @param target
     * @param states
     */
    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

};

/**
 * Estructura usada para el ordenamiento de los nodos
 * @param node1
 * @param node2
 * @return 
 */
struct OrderScene {

    inline bool operator()(const SceneNode* node1, const SceneNode* node2) {
        return ((node1->getWorldPosition().y + node1->getYOffset()) < (node2->getWorldPosition().y + node2->getYOffset()));
    }
};

#endif	/* SCENENODE_H */

