/* 
 * File:   StateStack.cpp
 * Author: dorian
 * 
 * Created on 13 de diciembre de 2014, 14:13
 */

#include "StateStack.h"

StateStack::StateStack(Context context) : stack(), pendingList(), context(context), factories() {
}

StateStack::~StateStack() {

}


void StateStack::update(sf::Time dt) {
    // Iterate from top to bottom, stop as soon as update() returns false
    for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr) {
        if (!(*itr)->update(dt))
            break;
    }

    applyPendingChanges();
}

void StateStack::draw() {
    // Draw all active states from bottom to top
    for (std::vector<State*>::iterator it = stack.begin(); it != stack.end(); ++it) {
        (*it)->draw();
    }
}

void StateStack::handleEvent(const sf::Event& event) {
    // Iterate from top to bottom, stop as soon as handleEvent() returns false
    for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr) {
        if (!(*itr)->handleEvent(event))
            break;
    }

    applyPendingChanges();
}

void StateStack::pushState(StatesID stateID) {
    pendingList.push_back(PendingChange(ActionStack::Push, stateID));
}

void StateStack::popState() {
    pendingList.push_back(PendingChange(ActionStack::Pop));
}

void StateStack::clearStates() {
    pendingList.push_back(PendingChange(ActionStack::Clear));
}

bool StateStack::isEmpty() const {
    return stack.empty();
}

State* StateStack::createState(StatesID stateID) {
    auto found = factories.find(stateID);
    assert(found != factories.end());
    return found->second;
}

void StateStack::applyPendingChanges() {

    for (PendingChange change : pendingList) {
        switch (change.action) {
            case ActionStack::Push:
                stack.push_back(createState(change.stateID));
                break;

            case ActionStack::Pop:
                stack.pop_back();
                break;

            case ActionStack::Clear:
                stack.clear();
                break;
        }
    }

    pendingList.clear();
}

