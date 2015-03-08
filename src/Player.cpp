/* 
 * File:   Player.cpp
 * Author: dorian
 * 
 * Created on 15 de febrero de 2015, 13:08
 */

#include "Player.h"
#include "Context.h"
#include "MoveCharacter.h"
#include "EntityNode.h"
#include <iostream>

Player::Player() {
    // Set initial key bindings
    keyBinding[sf::Keyboard::Left] = Actions::Left;
    keyBinding[sf::Keyboard::Right] = Actions::Right;
    keyBinding[sf::Keyboard::Up] = Actions::Up;
    keyBinding[sf::Keyboard::Down] = Actions::Down;
    
    // Set initial action bindings
    initializeActions();
}

void Player::initializeActions() {
    auto finder = [] (EntityNode& character, sf::Time) {
            character.accelerate(sf::Vector2f(-1,0) * character.getMaxSpeed());
            character.updateAnimation(Actions::Move);
        };
    
    actionBinding[Left].action = derivedAction<EntityNode>(finder);
            
            //MoveCharacter(-1, 0));
    actionBinding[Right].action = derivedAction<EntityNode>(MoveCharacter(+1, 0));
    actionBinding[Up].action = derivedAction<EntityNode>(MoveCharacter(0, -1));
    actionBinding[Down].action = derivedAction<EntityNode>(MoveCharacter(0, +1));
    
    actionBinding[Left].category = Category::CHARACTER;
    actionBinding[Right].category= Category::CHARACTER;
    actionBinding[Up].category = Category::CHARACTER;
    actionBinding[Down].category = Category::CHARACTER;
}

Player::~Player() {
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) {
    if (event.type == sf::Event::KeyPressed) {
        // Check if pressed key appears in key binding, trigger command if so
        auto found = keyBinding.find(event.key.code);

        if (found != keyBinding.end() ){ //&& !isRealtimeAction(found->second)){
            commands.push(actionBinding[found->second]);
        }
    }
}

void Player::handleRealtimeInput(CommandQueue& commands) {
    // Traverse all assigned keys and check if they are pressed
    for (auto pair : keyBinding) {
        // If key is pressed, lookup action and trigger corresponding command
        if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
            commands.push(actionBinding[pair.second]);
    }
}

bool Player::isRealtimeAction(Actions action) {
    switch (action) {
        case Left:
        case Right:
        case Down:
        case Up:
            return true;

        default:
            return false;
    }
}

void Player::assignKey(Actions action, sf::Keyboard::Key key) {
    // Remove all keys that already map to action
    for (auto itr = keyBinding.begin(); itr != keyBinding.end();) {
        if (itr->second == action)
            keyBinding.erase(itr++);
        else
            ++itr;
    }

    // Insert new binding
    keyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Actions action) const {
    for (auto pair : keyBinding) {
        if (pair.second == action)
            return pair.first;
    }

    return sf::Keyboard::Unknown;
}