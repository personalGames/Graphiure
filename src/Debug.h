/* 
 * File:   Debug.h
 * Author: dorian
 *
 * Created on 5 de abril de 2015, 18:48
 */

#ifndef DEBUG_H
#define	DEBUG_H

#include "Entity.h"
#include "SceneNode.h"

class Debug : public SceneNode{
public:
    Debug(Entity* entity);
    virtual ~Debug();
    void updateCurrent(sf::Time delta) ;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    Entity* entity;
};

#endif	/* DEBUG_H */

