/* 
 * File:   Life.cpp
 * Author: dorian
 * 
 * Created on 28 de marzo de 2015, 20:18
 */

#include "Life.h"
#include <iostream>

Life::Life(): Life(100) {

}

Life::Life(int maxLife): maxLife(maxLife), actualLife(maxLife) {

}

void Life::damage(int damage) {
    actualLife-=damage;
    if(actualLife<0){
        actualLife=0;
    }
}

bool Life::isAlive() {
    return actualLife>0;
}

Life::~Life() {

}
