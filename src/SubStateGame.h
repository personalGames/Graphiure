/* 
 * File:   SubStateGame.h
 * Author: dorian
 *
 * Created on 27 de abril de 2015, 20:43
 */

#ifndef SUBSTATEGAME_H
#define	SUBSTATEGAME_H

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

/**
 * Clase base para los subestados del juego
 */
class SubStateGame {
public:
    SubStateGame(): ended(false) {
    }
    virtual ~SubStateGame() {

    }

    
    virtual void draw()=0;
    virtual bool update(sf::Time delta)=0;
    virtual bool handleEvent(const sf::Event& event)=0;
    
    /**
     * Setea si el subestado ha terminado
     */
    void setEnded() {
        this->ended = true;
    }
    
    /**
     * Devuelve si el subestado del juego ha terminado
     * @return true si ha terminado
     */
    bool isEnded() const {
        return ended;
    }

private:
    /**
     * Guarda si el subestado ha terminado
     */
    bool ended;
};

#endif	/* SUBSTATEGAME_H */

