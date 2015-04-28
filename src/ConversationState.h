/* 
 * File:   ConversationState.h
 * Author: dorian
 *
 * Created on 27 de abril de 2015, 20:42
 */

#ifndef CONVERSATIONSTATE_H
#define	CONVERSATIONSTATE_H

#include "SystemObjectsGame.h"
#include "SubStateGame.h"
#include "IdEntity.h"
#include "SystemGraphic.h"
#include <string>
#include "SystemManager.h"

class ConversationState : SubStateGame {
public:
    ConversationState(IdEntity id, SystemManager* system);
    virtual ~ConversationState();
    
    virtual void draw();
    virtual bool update(sf::Time delta);
    virtual bool handleEvent(const sf::Event& event);
    
private:
    SystemObjectsGame* objects;
    SystemGraphic* graphics;
    sf::Text text;
};

#endif	/* CONVERSATIONSTATE_H */

