/* 
 * File:   GameState.cpp
 * Author: dorian
 * 
 * Created on 10 de febrero de 2015, 0:24
 */

#include "GameState.h"

GameState::GameState(StateStack& stack, Context* context) :
        State(stack, context),player(*context->player), systemManager(context->systemManager) {

}

void GameState::draw() {
    level->draw();
}

bool GameState::handleEvent(const sf::Event& event) {
        // Game input handling
        CommandQueue& commands = level->getCommandQueue();
        player.handleEvent(event, commands);

        // Escape pressed, trigger the pause screen
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            requestStackPush(StatesID::Pause);
    
    return true;
}

bool GameState::update(sf::Time dt) {
    level->update(dt);
    
    CommandQueue& commands = level->getCommandQueue();
    player.handleRealtimeInput(commands);
    
    return true;
}

void GameState::pushedAction(){
    level=context->actualLevel;
}