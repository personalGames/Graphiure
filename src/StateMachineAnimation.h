/* 
 * File:   StateMachineAnimation.h
 * Author: dorian
 *
 * Created on 9 de marzo de 2015, 21:09
 */

#ifndef STATEMACHINEANIMATION_H
#define	STATEMACHINEANIMATION_H

#include <vector>
#include "Animation.h"
#include "Actions.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "StateMachine.h"
#include "AnimatedSprite.h"

#include <iostream>

/**
 * Clase que representa una máquina de estados finitos y controla la animación
 * que se esté reproduciendo en el momento
 */
class StateMachineAnimation : sf::Drawable {
public:
    /**
     * Constructor
     * @param stateMachine
     */
    StateMachineAnimation(StateMachine &stateMachine);
    virtual ~StateMachineAnimation();
    /**
     * Añade una animación
     * @param animation animación a añadir
     */
    void addAnimation(Animation* animation);
    
    /**
     * Actualiza la animación actual
     * @param delta tiempo entre frame y frame
     */
    void update(sf::Time delta);
    /**
     * Actualiza la máquina de estados finitos con la entrada
     * @param action entrada para la máquina
     */
    void update(int action);
    /**
     * Actualiza la máquina de estados finitos con la entrada
     * @param action entrada para la máquina
     */
    inline void update(Actions action){ update(static_cast<int>(action)); };
    

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /**
     * Setea el vector de animaciones de la máquina
     * @param animations
     */
    void setAnimations(std::vector<Animation*>* animations);
    
private:
    /**
     * Actual state of animation of the entity
     */
    int actualState;
    /**
     * Set of animations of the entity
     */
    std::vector<Animation*>* animations;
    /**
     * Actual animation setted
     */
    AnimatedSprite actualAnimation;
    /**
     * State machine of animations
     */
    StateMachine stateMachine;
};

#endif	/* STATEMACHINEANIMATION_H */

