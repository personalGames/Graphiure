/* 
 * File:   StaticBlock.h
 * Author: dorian
 *
 * Created on 28 de marzo de 2015, 23:44
 */

#ifndef STATICBLOCK_H
#define	STATICBLOCK_H

#include "Entity.h"
#include "Collision.h"
#include "MessageCollision.h"
#include "OnCollision.h"
#include "GameObjects.h"


class StaticBlock : public GameObjects {
public:
    virtual ~StaticBlock() {

    }

    virtual Entity* prepareEntity(PropertyManager& parameters);
private:
    void makeOnCollision(IdEntity idObject, OnCollision* onCollision);
};

#endif	/* STATICBLOCK_H */

