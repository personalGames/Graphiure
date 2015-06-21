/* 
 * File:   SoundPlayer.h
 * Author: dorian
 *
 * Created on 16 de diciembre de 2014, 11:42
 */

#ifndef SOUNDPLAYER_H
#define	SOUNDPLAYER_H

#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "SoundEffectID.h"
#include <list>
#include "ResourceHolder.h"

/**
 * 
 */
class SoundPlayer : private sf::NonCopyable {
public:
    SoundPlayer();

    void play(SoundEffectID effect);
    void play(SoundEffectID effect, sf::Vector2f position);

    void removeStoppedSounds();
    void setListenerPosition(sf::Vector2f position);
    sf::Vector2f getListenerPosition() const;


private:
    ResourceHolder<SoundEffectID, sf::SoundBuffer> mSoundBuffers;
    std::list<sf::Sound> mSounds;
};

#endif	/* SOUNDPLAYER_H */

