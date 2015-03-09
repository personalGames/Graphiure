/* 
 * File:   StateMachineAnimation.cpp
 * Author: dorian
 * 
 * Created on 9 de marzo de 2015, 21:09
 */

#include "StateMachineAnimation.h"

StateMachineAnimation::StateMachineAnimation(StateMachine &stateMachine)
    :actualState(0),
    animations(),
    actualAnimation(),
    stateMachine(stateMachine){
}

void StateMachineAnimation::addAnimation(Animation* animation) {
    if (animation != nullptr) {
        animations.push_back(animation);
    }
}


StateMachineAnimation::~StateMachineAnimation() {
}

void StateMachineAnimation::update(int action) {
    int newState = stateMachine.processEntry(action);
    
    if(newState!=-1){
        actualState=newState;
        actualAnimation.play(*animations[actualState]);
    }
    
}

void StateMachineAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(actualAnimation, states);
    
}
