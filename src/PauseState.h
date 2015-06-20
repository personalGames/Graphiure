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
    sf::Sprite backgroundSprite;
    sf::Text pausedText;
    GUI::Container GUIContainer;
};

#endif	/* PAUSESTATE_H */

