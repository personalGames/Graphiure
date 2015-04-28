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

class SubStateGame {
public:
    SubStateGame(): ended(false) {
    }
    virtual ~SubStateGame() {

    }

    
    virtual void draw()=0;
    virtual bool update(sf::Time delta)=0;
    virtual bool handleEvent(const sf::Event& event)=0;
    
    void setEnded() {
        this->ended = true;
    }
    
    bool isEnded() const {
        return ended;
    }

private:
    bool ended;
};

#endif	/* SUBSTATEGAME_H */

