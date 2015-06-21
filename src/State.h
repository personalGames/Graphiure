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

class StateStack; //because StateStack has dependencies too with Stat. So
//to avoid circular dependencies

/**
 * Clase base de estados
 */
class State {
public:
    /**
     * Constructor
     * @param stack pila de estados
     * @param context contexto
     */
    State(StateStack& stack, Context* context);
    /**
     * Destructor
     */
    virtual ~State();
    
    /**
     * Dibuja el estado
     */
    virtual void draw()=0;
    /**
     * Actualiza el estado
     * @param delta tiempo entre frame y frame
     * @return true si se ha actualizado
     */
    virtual bool update(sf::Time delta)=0;
    /**
     * Procesa la entrada del usuario
     * @param event evento
     * @return true si lo ha procesado, false si no (o lo ha procesado pero que continúe)
     */
    virtual bool handleEvent(const sf::Event& event)=0;
    /**
     * Método ejecutado cuando es puesto en pila
     */
    virtual void pushedAction() { //nothing by default   
    };
    /**
     * Método ejecutado cuando es sacado de la pila
     */
    virtual void pulledAction(){};
    
protected:
    /**
     * PIla de estados
     */
    StateStack* stack;
    /**
     * Contexto de la aplicación
     */
    Context* context;
    
protected:
    /**
     * Pide poner un estado en pila
     * @param state identificador del estado
     */
    void requestStackPush(StatesID state);
    /**
     * PIde sacar el último estado de la pila
     */
    void requestStackPop();
    /**
     * Pide limpiar la pila
     */
    void requestStateClear();
    /**
     * Devuelve el contexto guardado en el estado
     * @return contexto
     */
    Context* getContext() const;

};

#endif	/* STATE_H */

