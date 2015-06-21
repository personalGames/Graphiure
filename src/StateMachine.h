/* 
 * File:   StateMachine.h
 * Author: dorian
 *
 * Created on 9 de marzo de 2015, 21:16
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

#include <vector>

/**
 * Estructura de transición para la máquina de estados finitos
 */
struct Transition{
    Transition(int state, int entry, int newState):
        state(state), entry(entry), newState(newState){};
    
    /**
     * Estado previo
     */
    int state;
    /**
     * Entrada
     */
    int entry;
    /**
     * Nuevo estado
     */
    int newState;
};

/**
 * Máquina de estados finitos
 */
class StateMachine {
public:
    /**
     * Constructor con el número de estados totales de la máquina
     * @param numberStates numero de estados que tiene
     */
    StateMachine(int numberStates);
    virtual ~StateMachine();
    
    /**
     * Añadir transición a la máquina
     * @param transition
     */
    void addTransition(Transition &transition);
    
    /**
     * devuelve el estado actual de la maquina
     * @return estado actual de la maquina
     */
    inline int getState(){ return state; }
    /**
     * Procesa la entrada y devuelve el nuevo estado
     * @param entry entrada para la maquina
     * @return nuevo estado de la máquina si hay transición o -1 si no lo hay
     */
    int processEntry(int entry);
    
private:
    /**
     * estado actual de la maquina
     */
    int state;
    /**
     * lista de transiciones
     */
    std::vector< std::vector<Transition> > transitions;
};

#endif	/* STATEMACHINE_H */

