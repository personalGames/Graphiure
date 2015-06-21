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
#include "LoadingLevel.h"
#include "Levels.h"

/**
 * Estado de carga
 */
class LoadingState : public State {
public:
    LoadingState(StateStack& stack, Context* context);

    virtual void draw();
    virtual bool update(sf::Time delta);
    virtual bool handleEvent(const sf::Event& event);

    /**
     * Establece el porcentaje de completado, modificando la barra de 
     * progeso acorde
     * @param percent porcentaje de 0 a 100 completado
     */
    void setCompletion(float percent);

private:
    /**
     * Texto de carga
     */
    sf::Text loadingText;
    /**
     * Fondo de barra de progreso
     */
    sf::RectangleShape progressBarBackground;
    /**
     * Barra de progreso
     */
    sf::RectangleShape progressBar;
    /**
     * Indica si la tarea ya ha sido creada
     */
    bool taskCreated;
    /**
     * Tarea que se ejecuta en paralelo mientras
     */
    ParallelTask* loadingTask;
};

#endif	/* LOADINGSTATE_H */

