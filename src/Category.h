/* 
 * File:   Category.h
 * Author: dorian
 *
 * Created on 16 de febrero de 2015, 20:16
 */

#ifndef CATEGORY_H
#define	CATEGORY_H

enum Category {
    NONE = 0,
    CHARACTER = 1<<0 //NEVER THE SAME NAME AS A CLASS!!!
//    PlayerAircraft = 1 << 1,
//    AlliedAircraft = 1 << 2,
//    EnemyAircraft = 1 << 3,
//    Pickup = 1 << 4,
//    AlliedProjectile = 1 << 5,
//    EnemyProjectile = 1 << 6,
//    ParticleSystem = 1 << 7,
//    SoundEffectCategory			= 1 << 8,

//    Aircraft = PlayerAircraft | AlliedAircraft | EnemyAircraft,
//    Projectile = AlliedProjectile | EnemyProjectile,
};

#endif	/* CATEGORY_H */

