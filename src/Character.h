/* 
 * File:   Character.h
 * Author: dorian
 *
 * Created on 15 de febrero de 2015, 14:13
 */

#ifndef CHARACTER_H
#define	CHARACTER_H

#include "Entity.h"
#include "Actions.h"
#include "ResourceHolder.h"
#include "Animation.h"
#include "AnimatedSprite.h"
#include "IDTextures.h"
#include <SFML/Graphics/RenderTarget.hpp>

class Character : public Entity {
public:
    Character(const ResourceHolder<IDTextures, sf::Texture>& textures);
    void initCharacter();
    virtual ~Character();

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

    float getMaxSpeed() const;
    virtual unsigned int getCategory() const;
    void updateAnimation(Actions action);

private:
    sf::Texture texture;
    AnimatedSprite animatedCharacter;
    std::vector<Animation*> animations;
    Actions lastAction;
    
    void adaptVelocity();
};

#endif	/* CHARACTER_H */

