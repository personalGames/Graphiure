/* 
 * File:   Weapon.h
 * Author: dorian
 *
 * Created on 18 de mayo de 2015, 9:45
 */

#ifndef WEAPON_H
#define	WEAPON_H

class Weapon {
public:
    Weapon(int damage, int range);
    Weapon(const Weapon& orig);
    virtual ~Weapon();
    
//    inline int getDamage() const {
//        return damage;
//    }
//
//    inline void setDamage(int damage) {
//        this->damage = damage;
//    }
//
//    inline int getExtraDamage() const {
//        return extraDamage;
//    }
//
//    inline void setExtraDamage(int extraDamage) {
//        this->extraDamage = extraDamage;
//    }
//
//    inline int getRange() const {
//        return range;
//    }
//
//    inline void setRange(int range) {
//        this->range = range;
//    }

    
private:
//    int damage;
//    int range;
//    int extraDamage;
};

#endif	/* WEAPON_H */

