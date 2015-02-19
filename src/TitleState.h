/* 
 * File:   TitleScreen.h
 * Author: dorian
 *
 * Created on 28 de diciembre de 2014, 12:18
 */

#ifndef TITLESCREEN_H
#define	TITLESCREEN_H

#include "State.h"
#include "Utilities.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

class TitleState : public State {
public:
    TitleState(StateStack& stack, Context* context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);


private:
    sf::Sprite backgroundSprite;
    sf::Text text;

    bool showText;
    sf::Time textEffectTime;
};

#endif	/* TITLESCREEN_H */

