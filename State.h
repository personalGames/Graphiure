/* 
 * File:   State.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 14:15
 */

#ifndef STATE_H
#define	STATE_H

#include "StatesID.h"
#include "Context.h"
#include <memory>

class StateStack; //because StateStack has dependencies too with State, so
//to avoid circular dependencies

class State {
public:
    State(StateStack& stack, Context context);
    virtual ~State();
    
    virtual void draw()=0;
    virtual bool update(sf::Time delta)=0;
    virtual bool handleEvent(const sf::Event& event)=0;
    
protected:
    StateStack* stack;
    Context context;
    
protected:
    void requestStackPush(StatesID state);
    void requestStackPop();
    void requestStateClear();
    Context getContext() const;

};

#endif	/* STATE_H */

