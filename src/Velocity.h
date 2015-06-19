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

class Velocity {
public:
    Velocity();
    Velocity(const Velocity& orig);
    virtual ~Velocity();
    
    inline sf::Vector2f getVelocity() const {
        return velocity;
    }

    void setVelocity(sf::Vector2f velocity) {
        this->velocity = velocity;
    }
    
    void setVelocity(float x, float y){
        this->velocity.x=x;
        this->velocity.y=y;
    }
    
    void incrementVelocity(float x, float y);
    void incrementVelocity(sf::Vector2f increment);
    
    void reset();
    void adaptVelocity();
    bool isQuiet();
    void updateVelocity(sf::Time dt, Position& actualPosition);
    

    void setMaxVelocity(float maxVelocity) {
        this->maxVelocity = maxVelocity;
    }

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
    
    inline bool isFreeze(){
        return freeze;
    }
    
    inline void setFreeze(bool freeze){
        this->freeze=freeze;
    }
    
private:
    sf::Vector2f velocity;
    float maxVelocity;
    bool freeze;
    
private:
    float getMagnitud() const;
};

#endif	/* VELOCITY_H */

