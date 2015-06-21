/* 
 * File:   PauseState.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 17:45
 */

#ifndef PAUSESTATE_H
#define	PAUSESTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Utilities.h"
#include "ResourceHolder.h"
#include "Container.h"
#include "Button.h"

/**
 * Estado de pausa, muestra algunos botones
 * @param stack
 * @param context
 */
class PauseState : public State {
public:
    PauseState(StateStack& stack, Context* context);
    ~PauseState();

    virtual void draw();
    virtual bool update(sf::Time delta);
    virtual bool handleEvent(const sf::Event& event);

    virtual void pushedAction();
    virtual void pulledAction();

private:
    /**
     * Texto de pausa
     */
    sf::Text pausedText;
    /**
     * Contenedor con los botones
     */
    GUI::Container GUIContainer;
};

#endif	/* PAUSESTATE_H */

