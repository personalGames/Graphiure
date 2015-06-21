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

/**
 * Estado del título inicial del juego
 */
class TitleState : public State {
public:
    /**
     * Constructor
     * @param stack pila de estados
     * @param context contexto
     */
    TitleState(StateStack& stack, Context* context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);


    virtual void pulledAction();
    virtual void pushedAction();



private:
    /**
     * Imagen de fondo
     */
    sf::Sprite backgroundSprite;
    /**
     * Texto a visualizar
     */
    sf::Text text;
    /**
     * Mostrar texto o no
     */
    bool showText;
    /**
     * Tiempo de parpadeo del texto
     */
    sf::Time textEffectTime;
};

#endif	/* TITLESCREEN_H */

