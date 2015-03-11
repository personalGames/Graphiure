/* 
 * File:   StructAnimation.h
 * Author: dorian
 *
 * Created on 11 de marzo de 2015, 11:16
 */

#ifndef STRUCTANIMATION_H
#define	STRUCTANIMATION_H

#include "Animation.h"

struct StructAnimation {
public:
    StructAnimation():animations(){};
    virtual ~StructAnimation(){};
    
    std::vector<Animation*>* animations;
};

#endif	/* STRUCTANIMATION_H */

