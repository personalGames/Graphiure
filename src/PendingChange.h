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


struct PendingChange {
    PendingChange(ActionStack action, StatesID stateID = StatesID::None);

    ActionStack action;
    StatesID stateID;
};

#endif	/* PENDINGCHANGE_H */

