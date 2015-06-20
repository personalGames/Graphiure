/* 
 * File:   MenuState.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 17:44
 */

#ifndef MENUSTATE_H
#define	MENUSTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Utilities.h"
#include "Component.h"
#include "Container.h"
#include "Button.h"
#include "ResourceHolder.h"

class MenuState : public State {
public:
    MenuState(StateStack& stack, Context* context);

    virtual void draw();
    virtual bool update(sf::Time delta);
    virtual bool handleEvent(const sf::Event& event);
    

    virtual void pulledAction();
    virtual void pushedAction();




private:
    sf::Sprite backgroundSprite;
    GUI::Container container;
};


#endif	/* MENUSTATE_H */

