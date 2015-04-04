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
#include "vector"


class SystemCollision : public ISystem{
public:
    SystemCollision(sf::FloatRect bounds);
    SystemCollision();
    virtual ~SystemCollision();
    

    virtual void initialize(){};
    virtual void finalize();
    virtual void update(sf::Time dt);
    virtual void updateSecondPart(sf::Time dt);
    virtual void registerEntity(Entity* entity);
    virtual void removedEntity(Entity* entity);


    void newWorldCollision(sf::FloatRect bounds);
    void clear();
    
    bool ContinuousCollisionDetection(Entity* one);
    void checkCollisions(sf::FloatRect region);
    bool checkCollisions(Entity* one, Entity* another);
    void correctInsidePosition(Entity* entity);
    std::vector<Entity*> checkCollisions(Entity* entity, float radius);
    void resolveCollisions();
    
private:
    QuadTree* tree;
    //queue
    std::queue<MessageCollision> queue;
};

#endif	/* SYSTEMCOLLISION_H */

