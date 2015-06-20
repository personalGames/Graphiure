/* 
 * File:   ChangeLevel.h
 * Author: dorian
 *
 * Created on 20 de junio de 2015, 16:29
 */

#ifndef CHANGELEVEL_H
#define	CHANGELEVEL_H

#include "GameObjects.h"
#include "Entity.h"
#include "Collision.h"
#include "OnCollision.h"
#include "Position.h"
#include "Message.h"
#include "Subject.h"
#include "PropertyManager.h"

#include <iostream>

class ChangeLevel : public GameObjects {
public:
    virtual ~ChangeLevel();
    virtual Entity* prepareEntity(PropertyManager& parameters);
private:
    void makeOnCollision(IdEntity idObject, OnCollision* onCollision);
};

#endif	/* CHANGELEVEL_H */

