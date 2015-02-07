/* 
 * File:   LoadingState.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 17:39
 */

#ifndef LOADINGSTATE_H
#define	LOADINGSTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "ParallelTask.h"
#include "Utilities.h"

class LoadingState : public State {
public:
    LoadingState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time delta);
    virtual bool handleEvent(const sf::Event& event);

    void setCompletion(float percent);

private:
    sf::Text loadingText;
    sf::RectangleShape progressBarBackground;
    sf::RectangleShape progressBar;

    ParallelTask loadingTask;
};

#endif	/* LOADINGSTATE_H */

