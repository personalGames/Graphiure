/* 
 * File:   Velocity.h
 * Author: dorian
 *
 * Created on 27 de marzo de 2015, 19:13
 */

#ifndef VELOCITY_H
#define	VELOCITY_H

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include "Position.h"

/**
 * Clase velocidad
 */
class Velocity {
public:
    /**
     * Constructor
     */
    Velocity();
    Velocity(const Velocity& orig);
    virtual ~Velocity();
    
    /**
     * Devuelve la velocidad
     * @return velocidad en forma de vector x,y
     */
    inline sf::Vector2f getVelocity() const {
        return velocity;
    }

    /**
     * Setea la nueva velocidad
     * @param velocity nueva velocidad
     */
    void setVelocity(sf::Vector2f velocity) {
        this->velocity = velocity;
    }
    
    /**
     * Setea la velocidad
     * @param x velocidad en el eje x
     * @param y velocidad en el eje y
     */
    void setVelocity(float x, float y){
        this->velocity.x=x;
        this->velocity.y=y;
    }
    
    /**
     * Incrementa la velocidad en x e y
     * @param x incremento en el eje x
     * @param y incremento en el eje y
     */
    void incrementVelocity(float x, float y);
    /**
     * Incrementa la velocidad
     * @param increment vector con el incremento
     */
    void incrementVelocity(sf::Vector2f increment);
    /**
     * Deja la velocidad a cero
     */
    void reset();
    /**
     * Ajusta la velocidad máxima
     */
    void adaptVelocity();
    /**
     * Comprueba si está quieto (no hay velocidad)
     * @return true si esta quieto
     */
    bool isQuiet();
    /**
     * Actualiza la posición dada con la velocidad que lleva 
     * @param dt tiempo transcurrido
     * @param actualPosition posición a modificar
     */
    void updateVelocity(sf::Time dt, Position& actualPosition);
    
    /**
     * Setea la velocidad máxima
     * @param maxVelocity máxima velocidad
     */
    void setMaxVelocity(float maxVelocity) {
        this->maxVelocity = maxVelocity;
    }

    /**
     * Devuelve la velocidad máxima
     * @return velocidad máxima
     */
    float getMaxVelocity() const {
        return maxVelocity;
    }

    inline bool operator==(const Velocity& lhs) const{
        return lhs.velocity == velocity;
    }

    inline bool operator!=(const Velocity& lhs) const {
        return !operator==(lhs);
    }

    inline bool operator<(const Velocity& lhs) const {
        
        return lhs.getMagnitud()<getMagnitud();
    }

    inline bool operator>(const Velocity& lhs) const {
        return operator<(lhs);
    }

    inline bool operator<=(const Velocity& lhs) const {
        return !operator>(lhs);
    }

    inline bool operator>=(const Velocity& lhs) const {
        return !operator<(lhs);
    }
    
    /**
     * Comprueba si está congelado y no puede moverse
     * @return true si no se puede mover (no se aplica velocidad)
     */
    inline bool isFreeze(){
        return freeze;
    }
    
    /**
     * Setea si se puede mover o no
     * @param freeze
     */
    inline void setFreeze(bool freeze){
        this->freeze=freeze;
    }
    
private:
    /**
     * Velocidad
     */
    sf::Vector2f velocity;
    /**
     * Máxima velocidad
     */
    float maxVelocity;
    /**
     * Si se puede mover o no
     */
    bool freeze;
    
private:
    /**
     * Devuelve la magnitud de la velocidad
     * @return 
     */
    float getMagnitud() const;
};

#endif	/* VELOCITY_H */

