/* 
 * File:   Position.h
 * Author: dorian
 *
 * Created on 29 de marzo de 2015, 11:53
 */

#ifndef POSITION_H
#define	POSITION_H

class Position {
public:
    Position();
    virtual ~Position();

    void updatePosition(float x, float y);
    
    inline sf::Transformable getPosition() const {
        return position;
    }

    inline void setPosition(sf::Transformable position) {
        this->position = position;
    }

    inline sf::Transformable getPreviousPosition() const {
        return previousPosition;
    }

    inline void setPreviousPosition(sf::Transformable previousPosition) {
        this->previousPosition = previousPosition;
    }
    
private:
    sf::Transformable position;
    sf::Transformable previousPosition;
};

#endif	/* POSITION_H */

