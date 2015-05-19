/* 
 * File:   StateMachineAnimation.h
 * Author: dorian
 *
 * Created on 9 de marzo de 2015, 21:09
 */

#ifndef STATEMACHINEANIMATION_H
#define	STATEMACHINEANIMATION_H

#include <vector>
#include "Animation.h"
#include "Actions.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "StateMachine.h"
#include "AnimatedSprite.h"

#include <iostream>


class StateMachineAnimation : sf::Drawable {
public:
    StateMachineAnimation(StateMachine &stateMachine);
    virtual ~StateMachineAnimation();
    
    void addAnimation(Animation* animation);
    
    void update(sf::Time delta);
    
    void update(int action);
    
    inline void update(Actions action){ update(static_cast<int>(action)); };
    

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void setAnimations(std::vector<Animation*>* animations);
    
private:
    /**
     * Actual state of animation of the entity
     */
    int actualState;
    /**
     * Set of animations of the entity
     */
    std::vector<Animation*>* animations;
    /**
     * Actual animation setted
     */
    AnimatedSprite actualAnimation;
    /**
     * State machine of animations
     */
    StateMachine stateMachine;
};

#endif	/* STATEMACHINEANIMATION_H */

