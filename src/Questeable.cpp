/* 
 * File:   Questeable.cpp
 * Author: dorian
 * 
 * Created on 7 de mayo de 2015, 12:54
 */

#include "Questeable.h"

Questeable::Questeable(int id): quest() {
    this->idQuest=id;
}

void Questeable::addPartQuest(PartQuest* quest) {
    this->quest.push_back(quest);
}


Questeable::Questeable(const Questeable& orig) {
    this->idQuest=orig.idQuest;
    this->quest=orig.quest;
}

Questeable::~Questeable() {
}