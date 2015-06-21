/* 
 * File:   Position.h
 * Author: dorian
 *
 * Created on 29 de marzo de 2015, 11:53
 */

#ifndef POSITION_H
#define	POSITION_H

#include <SFML/Graphics.hpp>

#include "CardinalPoints.h"

class Position {
public:
    Position();
    Position(Position& other);
    virtual ~Position();

    /**
     * Normal update
     * @param x
     * @param y
     */
    void updatePosition(float x, float y);
    
    /**
     * Devuelve la posición
     * @return la posición
     */
    inline sf::Transformable getPosition() const {
        return position;
    }

    /**
     * Setea una nueva posición y elimina la anterior (poniendo la misma posicion)
     * @param position nueva posición
     */
    inline void setPosition(sf::Transformable position) {
        this->previousPosition=position;
        this->position = position;
    }
    
    /**
     * Setea una nueva posición y elimina la anterior (poniendo la misma posicion) 
     * @param x posición x
     * @param y posición y
     */
    inline void setPosition(float x, float y){
        previousPosition.setPosition(x,y);
        position.setPosition(x,y);
    }
    
    /**
     * Incrementa la posición y guarda la previa
     * @param x incremento x
     * @param y incremento y
     */
    void setPositionIncrement(float x, float y);
   /**
    * Comprueba con la posición anterior y determina hacia que dirección está
    * mirando
    * @return uno de los cuatro puntos cardinales hacia los que está mirando 
    */
    CardinalPoints getDirection();
    
private:
    /**
     * posición actual
     */
    sf::Transformable position;
    /**
     * Posición previa
     */
    sf::Transformable previousPosition;
    /**
     * dirección de vista
     */
    CardinalPoints direction;
    /**
     * Devuelve el vector de movimiento entre la posición actual y la previa
     * @return vector de movimiento
     */
    sf::Vector2f getMoveVector();
};

#endif	/* POSITION_H */

