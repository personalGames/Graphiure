/* 
 * File:   Subject.h
 * Author: dorian
 *
 * Created on 27 de abril de 2015, 11:50
 */

#ifndef SUBJECT_H
#define	SUBJECT_H

#include <vector>
#include "Message.h"

/**
 * Clase vigilada por los observadores en el patrón observer
 */
class Subject {
private:
    // 1. "independent" functionality
    std::vector<class Observer*> views;
    //TODO: hacer vector de mensajes, por si se junta varios
    /**
     * EL mensaje que cambia
     */
    Message value; //el mensaje
public:
    /**
     * Constructor por defecto
     */
    Subject() : value() {
    }
    
    /**
     * Guarda un observador
     * @param obs observador
     */
    inline void attach(Observer *obs) {
        views.push_back(obs);
    }

    /**
     * Quita un observador
     * @param obs observador a quitar
     */
    inline void detach(Observer *obs);

    /**
     * Setea el mensaje y notifica a los observadores
     * @param val mensaje a setear
     */
    void setMessage(Message& val) {
        value = val;
        notify();
    }

    /**
     * Devuelve el mensaje
     * @return mensaje
     */
    Message getMessage() {
        return value;
    }

    /**
     * Notifica a los observadores de cambios
     */
    void notify();

};

#endif	/* SUBJECT_H */

