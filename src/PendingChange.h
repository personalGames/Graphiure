/* 
 * File:   PendingChange.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 14:42
 */

#ifndef PENDINGCHANGE_H
#define	PENDINGCHANGE_H

#include "StatesID.h"
#include "ActionStack.h"

/**
 * Estructura para guardar los cambios pendientes de hacer en la pila
 * de estados
 */
struct PendingChange {
    /**
     * Constructor
     * @param action sacar, limpiar, meter estado...
     * @param stateID identificador del estado. Por defecto ninguno
     */
    PendingChange(ActionStack action, StatesID stateID = StatesID::None);

    /**
     * Acción a realizar
     */
    ActionStack action;
    /**
     * Identificador del estado implicado
     */
    StatesID stateID;
};

#endif	/* PENDINGCHANGE_H */

