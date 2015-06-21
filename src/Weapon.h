/* 
 * File:   Weapon.h
 * Author: dorian
 *
 * Created on 18 de mayo de 2015, 9:45
 */

#ifndef WEAPON_H
#define	WEAPON_H

/**
 * Clase que define un arma
 */
class Weapon {
public:
    /**
     * Constructor con el daño que realiza y el rango que alcanza el ataque
     * @param damage daño
     * @param range alcance del arma
     */
    Weapon(int damage, int range);
    /**
     * Constructor copia
     * @param orig
     */
    Weapon(const Weapon& orig);
    /**
     * Destructor
     */
    virtual ~Weapon();
    
    /**
     * Devuelve el daño que realiza
     * @return daño que realiza
     */
    inline int getDamage() const {
        return damage;
    }

    /**
     * Setea el daño que hace el arma
     * @param damage daño que hace
     */
    inline void setDamage(int damage) {
        this->damage = damage;
    }

    /**
     * Devuelve un daño extra
     * @return daño extra
     */
    inline int getExtraDamage() const {
        return extraDamage;
    }

    /**
     * Setea un daño extra al arma
     * @param extraDamage daño extra
     */
    inline void setExtraDamage(int extraDamage) {
        this->extraDamage = extraDamage;
    }

    /**
     * Devuelve el rango del arma
     * @return rango del arma
     */
    inline int getRange() const {
        return range;
    }

    /**
     * Setea el rango del arma
     * @param range
     */
    inline void setRange(int range) {
        this->range = range;
    }

    
private:
    /**
     * daño del arma
     */
    int damage;
    /**
     * rando del arma
     */
    int range;
    /**
     * daño extra
     */
    int extraDamage;
};

#endif	/* WEAPON_H */

