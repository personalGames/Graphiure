/* 
 * File:   Questeable.cpp
 * Author: dorian
 * 
 * Created on 7 de mayo de 2015, 12:54
 */

#include "Questeable.h"

Questeable::Questeable(int id, PartQuest* quest) {
    this->idQuest=id;
    this->quest=quest;
}

Questeable::Questeable(const Questeable& orig) {
    this->idQuest=orig.idQuest;
    this->quest=orig.quest;
}

Questeable::~Questeable() {
}

bool Questeable::isDone() {
    return quest->IsDone();
}

void Questeable::setDone(bool done) {
    quest->SetDone(done);
}
