/* 
 * File:   State.cpp
 * Author: dorian
 * 
 * Created on 13 de diciembre de 2014, 14:15
 */

#include "State.h"
#include "StateStack.h" //included here because of declaration incomplete in header
//to avoid circular dependencies


State::State(StateStack& stack, Context context) : stack(&stack), context(context) {
}

State::~State() {
}

void State::requestStackPush(StatesID stateID) {
    stack->pushState(stateID);
}

void State::requestStackPop() {
    stack->popState();
}

void State::requestStateClear() {
    stack->clearStates();
}


Context State::getContext() const {
    return context;
}