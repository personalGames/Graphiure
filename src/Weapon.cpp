/* 
 * File:   Weapon.cpp
 * Author: dorian
 * 
 * Created on 18 de mayo de 2015, 9:45
 */

#include "Weapon.h"

Weapon::Weapon(int damage, int range): damage(damage), range(range), extraDamage(0) {
    
}


Weapon::Weapon(const Weapon& orig) {
    damage=orig.damage;
    range=orig.range;
    extraDamage=orig.extraDamage;
}

Weapon::~Weapon() {
    
}

