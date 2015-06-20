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
    Player();
    virtual ~Player();
    
    void initialize(SystemManager& managerSystem, SoundPlayer* mSound);
    
    void handleEvent(const sf::Event& event, CommandQueue& commands);
    void handleRealtimeInput(CommandQueue& commands);
    
    void assignKey(Actions action, sf::Keyboard::Key key);
    sf::Keyboard::Key getAssignedKey(Actions action) const;
    
private:
    SystemManager system;
    SoundPlayer* mSound;
    
    std::map<sf::Keyboard::Key, Actions> keyBinding;
    std::map<Actions, Command> actionBinding;
    
    void initializeActions();
    static bool isRealtimeAction(Actions action);
};

#endif	/* PLAYER_H */

