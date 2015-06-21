/* 
 * File:   GameState.h
 * Author: dorian
 *
 * Created on 10 de febrero de 2015, 0:24
 */

#ifndef GAMESTATE_H
#define	GAMESTATE_H

#include "StateStack.h"
#include "Level.h"

/**
 * Estado de juego
 */
class GameState : public State {
public:
    GameState(StateStack& stack, Context* context);
    
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);
    
    virtual void pushedAction();
    
private:
    /**
     * Nivel del juego
     */
    Level* level;
    /**
     * Tiempo transcurrido antes de visualizar game over
     */
    sf::Time mElapsedTime;
};

#endif	/* GAMESTATE_H */

