/* 
 * File:   ISystem.cpp
 * Author: dorian
 * 
 * Created on 22 de marzo de 2015, 14:09
 */

#include "ISystem.h"

ISystem::ISystem(): type(TypeSystem::NONE), initialized(false), finalized(false) {
}

ISystem::~ISystem() {
}

