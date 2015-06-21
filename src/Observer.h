/* 
 * File:   Observer.h
 * Author: dorian
 *
 * Created on 27 de abril de 2015, 11:49
 */

#ifndef OBSERVER_H
#define	OBSERVER_H

#include "Subject.h"

static int countObserver = 0;

/**
 * Observador del patrón observer
 */
class Observer {
    
private:
    // 2. "dependent" functionality
    Subject *model;
    /**
     * Identificador del observador
     */
    int id;
    
public:
    /**
     * Devuelve el identificador del observador
     * @return un número identificando al observador
     */
    inline int getId(){
        return id;
    }
    /**
     * Constructor
     */
    Observer(): id(countObserver){
        countObserver++;
    }
    /**
     * Setea el objeto a vigilar
     * @param mod objeto a vigilar
     */
    void setSubject(Subject* mod);
    /**
     * Método a ejecutar cuando haya cambios en el objeto vigilado
     */
    virtual void update() = 0;
    
protected:
    /**
     * Devuelve el objeto vigilado
     * @return objeto vigilado
     */
    inline Subject *getSubject() {
        return model;
    }

};

#endif	/* OBSERVER_H */

