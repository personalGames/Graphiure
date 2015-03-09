/* 
 * File:   StateMachine.h
 * Author: dorian
 *
 * Created on 9 de marzo de 2015, 21:16
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

#include <vector>

struct Transition{
    Transition(int state, int entry, int newState);;
    
    int state;
    int entry;
    int newState;
};

class StateMachine {
public:
    StateMachine(int numberTransitions);
    virtual ~StateMachine();
    
    void addTransition(Transition &transition);
    
    inline int getState(){ return state; }
    int processEntry(int entry);
    
private:
    int state;
    
    std::vector< std::vector<Transition> > transitions;
};

#endif	/* STATEMACHINE_H */

