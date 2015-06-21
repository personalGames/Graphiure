/* 
 * File:   Debug.h
 * Author: dorian
 *
 * Created on 5 de abril de 2015, 18:48
 */

#ifndef DEBUG_H
#define	DEBUG_H

#include "Entity.h"
#include "SceneNode.h"

/**
 * Nodo utilizado para debug, en el se dibujan los puntos de colisión de la entidad
 */
class Debug : public SceneNode{
public:
    /**
     * Constructor
     * @param entity entidad a comprobar su zona de colisión
     */
    Debug(Entity* entity);
    virtual ~Debug();
    /**
     * Actualiza la entidad/nodo
     * @param delta tiempo entre frame y frame
     */
    void updateCurrent(sf::Time delta) ;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    /**
     * Entidad del nodo
     */
    Entity* entity;
};

#endif	/* DEBUG_H */

