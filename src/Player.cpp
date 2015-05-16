/* 
 * File:   Player.cpp
 * Author: dorian
 * 
 * Created on 15 de febrero de 2015, 13:08
 */

#include "Player.h"
#include "Velocity.h"
#include "Behaviour.h"
#include "SystemCollision.h"
#include "Subject.h"

Player::Player() {

}

void Player::initialize(SystemManager& managerSystem) {
    this->system = managerSystem;
    // Set initial key bindings
    keyBinding[sf::Keyboard::Left] = Actions::Left;
    keyBinding[sf::Keyboard::Right] = Actions::Right;
    keyBinding[sf::Keyboard::Up] = Actions::Up;
    keyBinding[sf::Keyboard::Down] = Actions::Down;
    keyBinding[sf::Keyboard::E] = Actions::ActionPlayer;
    keyBinding[sf::Keyboard::Q] = Actions::ActionQuest;

    // Set initial action bindings
    initializeActions();
}

void Player::initializeActions() {
    auto finder123 = [this] (Entity& character, sf::Time) {
        SystemCollision* coll = static_cast<SystemCollision*> (system.getSystem(TypeSystem::COLLISION));
        sf::FloatRect query = character.Get<Collision*>("Collision")->getAABB();
        sf::Vector2f range=character.Get<sf::Vector2f>("query");

        Position* pos = character.Get<Position*>("Position");
        switch (pos->getDirection()) {
            case CardinalPoints::EAST:
                query.width+=range.x;
                break;
            case CardinalPoints::WEST:
                query.left-=range.x;
                query.width+=range.x;
                break;
            case CardinalPoints::SOUTH:
                query.height+=range.y;
                break;
            case CardinalPoints::NORTH:
                query.top-=range.y;
                query.height+=range.y;
                break;
        }

        std::vector<Entity*>* entities = coll->query(query);
        for (Entity* entity : *entities) {
            if (entity->getId() != character.getId() && entity->HasID("Behaviour")) {
                switch (pos->getDirection()) {
                    case CardinalPoints::EAST:
                        entity->Get<StateMachineAnimation*>("Drawable")->update(Actions::Left);
                        break;
                    case CardinalPoints::WEST:
                        entity->Get<StateMachineAnimation*>("Drawable")->update(Actions::Right);
                        break;
                    case CardinalPoints::SOUTH:
                        entity->Get<StateMachineAnimation*>("Drawable")->update(Actions::Up);
                        break;
                    case CardinalPoints::NORTH:
                        entity->Get<StateMachineAnimation*>("Drawable")->update(Actions::Down);
                        break;
                }
                entity->Get<Behaviour*>("Behaviour")->behaviourFunction(Actions::ActionPlayer);
            }
        }
    };
    actionBinding[Actions::ActionPlayer].action = derivedAction<Entity>(finder123);
    
    auto finder12 = [this] (Entity& character, sf::Time) {
        character.Get<Behaviour*>("Behaviour")->behaviourFunction(Actions::ActionQuest);
    };
    actionBinding[Actions::ActionQuest].action = derivedAction<Entity>(finder12);
    
    auto finder = [] (Entity& character, sf::Time) {
        character.Get<Velocity*>("Velocity")->incrementVelocity(sf::Vector2f(-1, 0));
        character.Get<StateMachineAnimation*>("Drawable")->update(Actions::Left);
    };
    actionBinding[Left].action = derivedAction<Entity>(finder);


    auto finder2 = [] (Entity& character, sf::Time) {
        character.Get<Velocity*>("Velocity")->incrementVelocity(sf::Vector2f(1, 0));
        character.Get<StateMachineAnimation*>("Drawable")->update(Actions::Right);
    };
    actionBinding[Right].action = derivedAction<Entity>(finder2);


    auto finder3 = [] (Entity& character, sf::Time) {
        character.Get<Velocity*>("Velocity")->incrementVelocity(sf::Vector2f(0, -1));
        character.Get<StateMachineAnimation*>("Drawable")->update(Actions::Up);
    };
    actionBinding[Up].action = derivedAction<Entity>(finder3);


    auto finder4 = [] (Entity& character, sf::Time) {
        character.Get<Velocity*>("Velocity")->incrementVelocity(sf::Vector2f(0, 1));
        character.Get<StateMachineAnimation*>("Drawable")->update(Actions::Down);
    };
    actionBinding[Down].action = derivedAction<Entity>(finder4);

    auto finder5 = [] (Entity& character, sf::Time) {
        character.Get<Velocity*>("Velocity")->incrementVelocity(sf::Vector2f(1, 1));
        character.Get<StateMachineAnimation*>("Drawable")->update(Actions::RightDown);
    };
    actionBinding[RightDown].action = derivedAction<Entity>(finder5);

    auto finder6 = [] (Entity& character, sf::Time) {
        character.Get<Velocity*>("Velocity")->incrementVelocity(sf::Vector2f(-1, 1));
        character.Get<StateMachineAnimation*>("Drawable")->update(Actions::LeftDown);
    };
    actionBinding[LeftDown].action = derivedAction<Entity>(finder6);

    auto finder7 = [] (Entity& character, sf::Time) {
        character.Get<Velocity*>("Velocity")->incrementVelocity(sf::Vector2f(1, -1));

        character.Get<StateMachineAnimation*>("Drawable")->update(Actions::RightUp);
    };
    actionBinding[RightUp].action = derivedAction<Entity>(finder7);

    auto finder8 = [] (Entity& character, sf::Time) {
        character.Get<Velocity*>("Velocity")->incrementVelocity(sf::Vector2f(-1, -1));
        character.Get<StateMachineAnimation*>("Drawable")->update(Actions::LeftUp);
    };
    actionBinding[LeftUp].action = derivedAction<Entity>(finder8);


    actionBinding[RightUp].category = Category::CHARACTER;
    actionBinding[LeftDown].category = Category::CHARACTER;
    actionBinding[RightDown].category = Category::CHARACTER;
    actionBinding[LeftUp].category = Category::CHARACTER;
    actionBinding[Left].category = Category::CHARACTER;
    actionBinding[Right].category = Category::CHARACTER;
    actionBinding[Up].category = Category::CHARACTER;
    actionBinding[Down].category = Category::CHARACTER;
    actionBinding[ActionPlayer].category = Category::CHARACTER;
    actionBinding[ActionQuest].category = Category::CHARACTER;
}

Player::~Player() {
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) {
    if (event.type == sf::Event::KeyPressed) {
        // Check if pressed key appears in key binding, trigger command if so
        auto found = keyBinding.find(event.key.code);

        if (found != keyBinding.end() && !isRealtimeAction(found->second)) {
            commands.push(actionBinding[found->second]);
        }
    }
}

void Player::handleRealtimeInput(CommandQueue& commands) {
    // Traverse all assigned keys and check if they are pressed
    //        for (auto pair : keyBinding) {
    //            // If key is pressed, lookup action and trigger corresponding command
    //            if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
    //                commands.push(actionBinding[pair.second]);
    //        }



    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        commands.push(actionBinding[LeftDown]);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        commands.push(actionBinding[LeftUp]);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        commands.push(actionBinding[RightUp]);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        commands.push(actionBinding[RightDown]);

    } else {
        for (auto pair : keyBinding) {
            // If key is pressed, lookup action and trigger corresponding command
            if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
                commands.push(actionBinding[pair.second]);
        }
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