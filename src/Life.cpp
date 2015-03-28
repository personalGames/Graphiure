/* 
 * File:   Life.cpp
 * Author: dorian
 * 
 * Created on 28 de marzo de 2015, 20:18
 */

#include "Life.h"

Life::Life(): Life(100) {

}

Life::Life(int maxLife): maxLife(maxLife), actualLife(maxLife) {

}

void Life::damage(int damage) {
    actualLife-=damage;
}

bool Life::isAlive() {
    return actualLife>0;
}

Life::~Life() {

}
