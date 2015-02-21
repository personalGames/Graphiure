/* 
 * File:   Character.cpp
 * Author: dorian
 * 
 * Created on 15 de febrero de 2015, 14:13
 */


#include "Character.h"

namespace DataStructureCharacter {
    enum AnimeDirections {
        Up = 0,
        Down = 1,
        Rigth,
        Left,
        EnumCount
    };
};

Character::Character(const ResourceHolder<IDTextures, sf::Texture>& textures) :
texture(textures.get(IDTextures::Player)),
animatedCharacter(sf::seconds(0.2), true, false), lastAction(Actions::None) {
    initCharacter();
}

void Character::initCharacter() {
    //first four positions are walking animation
    for (int i = 0; i < 4; i++) {
        Animation* walk = new Animation();
        walk->setSpriteSheet(texture);
        switch (i) {
            case DataStructureCharacter::AnimeDirections::Up:
                walk->addFrame(sf::IntRect(32, 96, 32, 32));
                walk->addFrame(sf::IntRect(64, 96, 32, 32));
                walk->addFrame(sf::IntRect(32, 96, 32, 32));
                walk->addFrame(sf::IntRect(0, 96, 32, 32));
                break;
            case DataStructureCharacter::AnimeDirections::Down:
                walk->addFrame(sf::IntRect(32, 0, 32, 32));
                walk->addFrame(sf::IntRect(64, 0, 32, 32));
                walk->addFrame(sf::IntRect(32, 0, 32, 32));
                walk->addFrame(sf::IntRect(0, 0, 32, 32));

                break;
            case DataStructureCharacter::AnimeDirections::Rigth:
                walk->addFrame(sf::IntRect(32, 64, 32, 32));
                walk->addFrame(sf::IntRect(64, 64, 32, 32));
                walk->addFrame(sf::IntRect(32, 64, 32, 32));
                walk->addFrame(sf::IntRect(0, 64, 32, 32));
                break;
            case DataStructureCharacter::AnimeDirections::Left:
                walk->addFrame(sf::IntRect(32, 32, 32, 32));
                walk->addFrame(sf::IntRect(64, 32, 32, 32));
                walk->addFrame(sf::IntRect(32, 32, 32, 32));
                walk->addFrame(sf::IntRect(0, 32, 32, 32));
                break;
        }
        animations.push_back(std::move(walk));
    }
    animatedCharacter.play(*animations[0]);
    animatedCharacter.setPosition(200, 200);
}

Character::~Character() {
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(animatedCharacter, states);
}

void Character::updateCurrent(sf::Time dt, CommandQueue& commands) {
    adaptVelocity();
    animatedCharacter.update(dt);
    Entity::updateCurrent(dt, commands);
    this->getPosition();
}

void Character::adaptVelocity() {
    sf::Vector2f velocity = this->getVelocity();

    // If moving diagonally, reduce velocity (to have always same velocity)
    if (velocity.x != 0.f && velocity.y != 0.f) {
        this->setVelocity(velocity / std::sqrt(2.f));
        
    //if none, stop the animation
    } else if (velocity.x == 0 && velocity.y == 0) {
        animatedCharacter.stop();
    }
}

float Character::getMaxSpeed() const {
    return 100.f;
}

void Character::updateAnimation(Actions action) {
    switch (action) {
        case Move:
        {
            Actions concreteAction = Actions::None;
            sf::Vector2f vel = getVelocity();
            if (vel.x != 0 && vel.y != 0) {
                //do nothing, just continue
                //here must be control what animation to be seen when diagonal;
                //                concreteAction = lastAction;
            } else if (vel.y != 0) {
                concreteAction = (vel.y > 0) ? Actions::Down : Actions::Up;
                lastAction = concreteAction;
            } else {
                concreteAction = (vel.x > 0) ? Actions::Right : Actions::Left;
                lastAction = concreteAction;
            }
            updateAnimation(concreteAction);


            break;
        }
        case Up:
            animatedCharacter.play(*animations[DataStructureCharacter::AnimeDirections::Up]);
            break;
        case Down:
            animatedCharacter.play(*animations[DataStructureCharacter::AnimeDirections::Down]);
            break;
        case Right:
            animatedCharacter.play(*animations[DataStructureCharacter::AnimeDirections::Rigth]);
            break;
        case Left:
            animatedCharacter.play(*animations[DataStructureCharacter::AnimeDirections::Left]);
            break;
        default:
            break;
    }
}

unsigned int Character::getCategory() const {
    return Category::CHARACTER;
}
