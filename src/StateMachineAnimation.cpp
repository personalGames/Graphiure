/* 
 * File:   StateMachineAnimation.cpp
 * Author: dorian
 * 
 * Created on 9 de marzo de 2015, 21:09
 */

#include "StateMachineAnimation.h"
#include <iostream>

StateMachineAnimation::StateMachineAnimation(StateMachine &stateMachine)
: actualState(0),
animations(),
actualAnimation(),
stateMachine(stateMachine) {
}

void StateMachineAnimation::setAnimations(std::vector<Animation*>* animations) {
    this->animations = animations;
    actualAnimation.play(*((*animations)[1]));
    actualAnimation.setLooped(((*animations)[1])->getReplay());
}

void StateMachineAnimation::addAnimation(Animation* animation) {
    if (animation != nullptr) {
        animations->push_back(animation);
    }
}

StateMachineAnimation::~StateMachineAnimation() {
}

void StateMachineAnimation::update(sf::Time delta) {
    actualAnimation.update(delta);
}

void StateMachineAnimation::update(int action) {
    if (actualAnimation.getWait() && actualAnimation.isPlaying() && action == 0) {
        return;
    } else {
        int newState = stateMachine.processEntry(action);
        if (newState != -1) {
            actualState = newState;
            actualAnimation.play(*((*animations)[actualState]));
            actualAnimation.setLooped(((*animations)[actualState])->getReplay());
            actualAnimation.setWait(((*animations)[actualState])->getWait());
        }
    }
}

void StateMachineAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(actualAnimation, states);
}
