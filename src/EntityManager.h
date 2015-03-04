/* 
 * File:   EntityManager.h
 * Author: dorian
 *
 * Created on 4 de marzo de 2015, 11:51
 * 
 * We want to be able to use the entity ID as a weak reference. I.e., given an 
 * entity ID we want to be able to tell if it refers to a living entity or not.
 * 
 * Having a weak reference system is important, because if we only have strong 
 * references then if the entity dies we must notify everybody that might 
 * possibly hold a reference to the entity so that they can delete it. This is 
 * both costly and complicated. Especially since references might be held by 
 * other threads or by Lua code.
 * To enable weak referencing, we use the EntityManager class to keep track of 
 * all live entities.
 */

#ifndef ENTITYMANAGER_H
#define	ENTITYMANAGER_H

class EntityManager {
public:
    EntityManager();
    EntityManager(const EntityManager& orig);
    virtual ~EntityManager();
private:

};

#endif	/* ENTITYMANAGER_H */

