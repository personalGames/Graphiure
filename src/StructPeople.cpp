/* 
 * File:   StructPeople.h
 * Author: dorian
 *
 * Created on 20 de junio de 2015, 21:52
 */

#include "StructPeople.h"

StructPeople::StructPeople() {
    villagers=new std::vector<std::string*>();
}

StructPeople::~StructPeople() {
    delete villagers;
    delete character;
}
