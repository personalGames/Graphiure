/* 
 * File:   PartQuest.cpp
 * Author: dorian
 * 
 * Created on 7 de mayo de 2015, 11:26
 */

#include "PartQuest.h"

PartQuest::PartQuest(TypeQuest type, IdEntity destiny, IdEntity origin): PartQuest(type, destiny, origin, Actions::ActionPlayer){
    
}

PartQuest::PartQuest(TypeQuest type, IdEntity destiny, IdEntity origin, Actions action){
    this->type=type;
    this->idDestiny=destiny;
    this->idOrigin=origin;
    this->action=action;
}

PartQuest::PartQuest(const PartQuest& orig) {
    type=orig.type;
    idDestiny=orig.idDestiny;
    idOrigin=orig.idOrigin;
    action=orig.action;
}

PartQuest::~PartQuest() {
}

