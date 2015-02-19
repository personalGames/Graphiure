/* 
 * File:   Character.cpp
 * Author: dorian
 * 
 * Created on 15 de febrero de 2015, 14:13
 */


#include "Character.h"
#include <iostream>

Character::Character(const ResourceHolder<IDTextures, sf::Texture>& textures) : 
        texture(textures.get(IDTextures::Player)),
        animatedCharacter(sf::seconds(0.2), true, false){
    initCharacter();
}

void Character::initCharacter() {
    // set up the animations for all four directions (set spritesheet and push frames)
    Animation* walkingAnimationDown=new Animation();
    walkingAnimationDown->setSpriteSheet(texture);
    walkingAnimationDown->addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown->addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown->addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown->addFrame(sf::IntRect(0, 0, 32, 32));
    animations.push_back(std::move(walkingAnimationDown));

    Animation* walkingAnimationLeft=new Animation();
    walkingAnimationLeft->setSpriteSheet(texture);
    walkingAnimationLeft->addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft->addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft->addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft->addFrame(sf::IntRect(0, 32, 32, 32));
    animations.push_back(std::move(walkingAnimationLeft));

    Animation* walkingAnimationRight=new Animation();
    walkingAnimationRight->setSpriteSheet(texture);
    walkingAnimationRight->addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight->addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight->addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight->addFrame(sf::IntRect(0, 64, 32, 32));
    animations.push_back(std::move(walkingAnimationRight));

    Animation* walkingAnimationUp=new Animation();
    walkingAnimationUp->setSpriteSheet(texture);
    walkingAnimationUp->addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp->addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp->addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp->addFrame(sf::IntRect(0, 96, 32, 32));
    animations.push_back(std::move(walkingAnimationUp));
    
    animatedCharacter.play(*animations[0]);
    animatedCharacter.setPosition(200,200);
}


Character::~Character() {
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(animatedCharacter, states);
}

void Character::updateCurrent(sf::Time dt, CommandQueue& commands) {
    animatedCharacter.update(dt);
    sf::Vector2f vel=getVelocity();
    if(vel.x==0 && vel.y==0){
        animatedCharacter.stop();
    }
    Entity::updateCurrent(dt, commands);
}

float Character::getMaxSpeed() const {
    return 100.f;
}

void Character::updateAction(float x, float y) {
    if (x != 0) {
        if (x > 0) {
            animatedCharacter.play(*animations[2]);
        } else {
            animatedCharacter.play(*animations[1]);
        }
    } else if (y != 0) {
        if (y < 0) {
            animatedCharacter.play(*animations[3]);
        } else {
            animatedCharacter.play(*animations[0]);
        }
    } else {
        animatedCharacter.stop();
    }
}

unsigned int Character::getCategory() const {
    return Category::CharacterFUCKK;
}
