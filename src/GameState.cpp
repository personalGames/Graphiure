/* 
 * File:   GameState.cpp
 * Author: dorian
 * 
 * Created on 10 de febrero de 2015, 0:24
 */

#include "GameState.h"

GameState::GameState(StateStack& stack, Context* context) :
State(stack, context), systemManager(context->systemManager) {
    //player(*context->player)
    
    
}

void GameState::draw() {
    level->draw();
}

bool GameState::handleEvent(const sf::Event& event) {
    // Game input handling
    if (!level->isEnd()) {
        level->handleEvent(event);

        // Escape pressed, trigger the pause screen
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
            requestStackPush(StatesID::Pause);
        }
    }
    return true;
}

bool GameState::update(sf::Time dt) {
    level->update(dt);
    
    //check if player is alive
    if (level->isEnd()) {
        // Show state for 3 seconds, after return to menu
        mElapsedTime += dt;
        if (mElapsedTime > sf::seconds(2)) {
            requestStackPush(StatesID::GameOver);
        }

    }else if(level->changeLevel()){
        std::string* newLevel=level->getNextLevel();
        context->nameLevel=newLevel;
        
        requestStackPop();
        requestStackPush(StatesID::Loading);
    }
    
    return true;
}

void GameState::pushedAction() {
    mElapsedTime = sf::Time::Zero;
    level = context->actualLevel;
    level->setPlayer(context->player);
    // Play game theme
    context->music->play(MusicID::MissionTheme);
}