/* 
 * File:   StateStack.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 14:13
 */

#ifndef STATESTACK_H
#define	STATESTACK_H

#include <vector>
#include <utility>
#include <functional>
#include <map>

#include "PendingChange.h"
#include "Context.h"
#include "StatesID.h"
#include "State.h"

class StateStack : private sf::NonCopyable {
public:
    StateStack(Context context);
    virtual ~StateStack();

    template <typename T>
    void registerState(StatesID stateID);

    void update(sf::Time dt);
    void draw();
    void handleEvent(const sf::Event& event);

    void pushState(StatesID stateID);
    void popState();
    void clearStates();

    bool isEmpty() const;



private:
    std::vector< State* > stack;
    std::vector<PendingChange> pendingList;
    Context context;
    std::map<StatesID, State*> factories;

    State* createState(StatesID stateID);
    void applyPendingChanges();

};

template <typename T>
void StateStack::registerState(StatesID stateID) {
    factories[stateID] = (new T(*this, &context));
}
#endif	/* STATESTACK_H */

