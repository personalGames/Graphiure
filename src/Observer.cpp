/* 
 * File:   Observer.cpp
 * Author: dorian
 * 
 * Created on 27 de abril de 2015, 11:49
 */

#include "Observer.h"

void Observer::setSubject(Subject* mod){
    model=mod;
    // 4. Observers register themselves with the Subject
    model->attach(this);
}