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
#include "Position.h"
#include "ActionStack.h"
#include "OnCollision.h"
#include "Velocity.h"
#include "Triangle.h"
#include "DelaunayTriangulation.h"


class SystemCollision : public ISystem {
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
    
    std::vector<Entity*>* query(sf::FloatRect query);
    void checkCollisions(sf::FloatRect region);
    void correctInsidePosition(Entity* entity);
    std::vector<Entity*> checkCollisions(Entity* entity, float radius);
    void resolveCollisions();
    
private:
    QuadTree* tree;
    //queue
    std::queue<MessageCollision*> queue;
    
    MessageCollision* triangulate(Collision* first, Collision* second, float time);
    MessageCollision* collisionDetection(Entity* one, Entity* two);
    MessageCollision* firstTimeCollision(Entity* one, Entity* two);
    MTV checkCollisions(Triangle& poly1, Triangle& poly2, bool detailed);
};

#endif	/* SYSTEMCOLLISION_H */

