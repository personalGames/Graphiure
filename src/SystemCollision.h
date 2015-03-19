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


class SystemCollision {
public:
    SystemCollision(sf::FloatRect bounds);
    virtual ~SystemCollision();
    
    void checkCollisions();
    bool checkCollisions(Entity* one, Entity* another);
    void update();
    void addCollisionable(Entity* entity);
    
private:
    QuadTree tree;
    //queue
    std::queue<MessageCollision> queue;
};

#endif	/* SYSTEMCOLLISION_H */

