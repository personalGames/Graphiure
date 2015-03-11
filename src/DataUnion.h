/* 
 * File:   DataUnion.h
 * Author: dorian
 *
 * Created on 9 de marzo de 2015, 23:16
 */

#ifndef DATAUNION_H
#define	DATAUNION_H

#include "StructMap.h"
#include "StructAnimation.h"

union DataUnion{
    StructMap* map;
    Animation* animation;
    StructAnimation* animations;
};

#endif	/* DATAUNION_H */

