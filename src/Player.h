/* 
 * File:   Player.h
 * Author: dorian
 *
 * Created on 15 de febrero de 2015, 13:08
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "Actions.h"
#include "Animation.h"
#include <SFML/Window.hpp>
#include "Command.h"
#include "CommandQueue.h"
#include <map>
#include <algorithm>
#include "Entity.h"
#include "StateMachineAnimation.h"

#include "SystemManager.h"
#include "SoundPlayer.h"

class Player {
public:
    /**
     * Constructor
     */
    Player();
    /**
     * Destructor
     */
    virtual ~Player();
    /**
     * Inicializa el jugador, estableciendo la entrada a la que reacciona
     * @param managerSystem gestor de sistemas del que pillará la información que necesite
     * @param mSound reproductor de sonidos para reproducir ante eventos
     */
    void initialize(SystemManager& managerSystem, SoundPlayer* mSound);
    /**
     * Procesa la entrada, creando si es necesario un comando a ejecutar
     * que deja en la pila de comandos
     * @param event evento
     * @param commands pila de comandos
     */
    void handleEvent(const sf::Event& event, CommandQueue& commands);
    /**
     * Procesa la entrada en tiempo real, creando si es necesario un comando a ejecutar
     * que deja en la pila de comandos
     * @param event evento
     * @param commands pila de comandos
     */
    void handleRealtimeInput(CommandQueue& commands);
    /**
     * Asigna una tecla a una determinada acción
     * @param action acción a setear
     * @param key código de tecla asociada a la acción
     */
    void assignKey(Actions action, sf::Keyboard::Key key);
    /**
     * Recupera la tecla asociada a una acción
     * @param action acción consultada
     * @return tecla asociada
     */
    sf::Keyboard::Key getAssignedKey(Actions action) const;
    
private:
    /**
     * Gestor de sistemas
     */
    SystemManager system;
    /**
     * Reproductor de sonidos
     */
    SoundPlayer* mSound;
    /**
     * Mapa entre teclas y acciones
     */
    std::map<sf::Keyboard::Key, Actions> keyBinding;
    /**
     * Mapa entre acciones y comandos a ejecutar
     */
    std::map<Actions, Command> actionBinding;
    /**
     * Establece las acciones para las teclas asociadas
     */
    void initializeActions();
    /**
     * Determina si la acción se considera una acción para comprobar en tiempo real
     * @param action accion que se consulta
     * @return true si se comprueba en tiempo real
     */
    static bool isRealtimeAction(Actions action);
};

#endif	/* PLAYER_H */

