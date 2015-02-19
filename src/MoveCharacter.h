/* 
 * File:   MoveCharacter.h
 * Author: dorian
 *
 * Created on 15 de febrero de 2015, 15:13
 */

#ifndef MOVECHARACTER_H
#define	MOVECHARACTER_H
#include "Character.h"

struct MoveCharacter {

    MoveCharacter(float vx, float vy) : velocity(vx, vy) {
    }

    void operator() (Character & character, sf::Time) const {
        character.accelerate(velocity * character.getMaxSpeed());
        character.updateAnimation(Actions::Move);
    }

    sf::Vector2f velocity;
};

#endif	/* MOVECHARACTER_H */

