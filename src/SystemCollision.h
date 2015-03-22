/* 
 * File:   SystemCollision.h
 * Author: dorian
 *
 * Created on 15 de marzo de 2015, 21:47
 */

#ifndef SYSTEMCOLLISION_H
#define	SYSTEMCOLLISION_H

#include "QuadTree.h"
#include "MessageCollision.h"
#include <queue>
#include "Collision.h"
#include "ISystem.h"


class SystemCollision: public ISystem{
public:
    SystemCollision(sf::FloatRect bounds);
    virtual ~SystemCollision();
    

    virtual void initialize(){};
    virtual void finalize();
    virtual void update();
    virtual void updateSecondPart(){};
    virtual void registerEntity(Entity* entity);



    void clear();
    
    void checkCollisions(sf::FloatRect region);
    bool checkCollisions(Entity* one, Entity* another);
    
private:
    QuadTree tree;
    //queue
    std::queue<MessageCollision> queue;
};

#endif	/* SYSTEMCOLLISION_H */

