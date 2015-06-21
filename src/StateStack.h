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

/**
 * Pila de estados
 * @param context contexto de la aplicación
 */
class StateStack : private sf::NonCopyable {
public:
    /**
     * Constructor
     * @param context
     */
    StateStack(Context context);
    /**
     * Destructor
     */
    virtual ~StateStack();

    /**
     * Registra un estado en la pila
     * @param stateID
     */
    template <typename T>
    void registerState(StatesID stateID);
    /**
     * Actualiza los estados de la pila
     * @param dt tiempo entre frame y frame
     */
    void update(sf::Time dt);
    /**
     * Dibuja los estados de la pila
     */
    void draw();
    /**
     * Procesa los eventos delegándolos en los estados de la pila
     * @param event
     */
    void handleEvent(const sf::Event& event);
    /**
     * Coloca un estado en la pila
     * @param stateID id del estado a colocar
     */
    void pushState(StatesID stateID);
    /**
     * Saca el último estado de la pila
     */
    void popState();
    /**
     * Limpia la pila de estados
     */
    void clearStates();
    /**
     * Comprueba si la pila está vacía
     * @return true si la pila está vacía
     */
    bool isEmpty() const;



private:
    /**
     * PIla de estados
     */
    std::vector< State* > stack;
    /**
     * Lista de cambios pendientes
     */
    std::vector<PendingChange> pendingList;
    /**
     * Contexto de la aplicación
     */
    Context context;
    /**
     * Relación de identificador de estados con el estado creado
     */
    std::map<StatesID, State*> factories;
    /**
     * Devuelve un estado dado su id
     * @param stateID id del estado a buscar
     * @return el estado
     */
    State* createState(StatesID stateID);
    /**
     * Aplica los cambios pendientes
     */
    void applyPendingChanges();

};

/**
 * Plantilla para el registro de estados. Crea el estado que registra
 * @param stateID identificador del estado
 */
template <typename T>
void StateStack::registerState(StatesID stateID) {
    factories[stateID] = (new T(*this, &context));
}

#endif	/* STATESTACK_H */

