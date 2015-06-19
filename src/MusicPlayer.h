/* 
 * File:   MusicPlayer.h
 * Author: dorian
 *
 * Created on 16 de diciembre de 2014, 11:25
 */

#ifndef MUSICPLAYER_H
#define	MUSICPLAYER_H

#include "MusicID.h"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>

class MusicPlayer : private sf::NonCopyable {
public:
    MusicPlayer();

    void play(MusicID theme);
    void stop();

    void setPaused(bool paused);
    void setVolume(float volume);


private:
    sf::Music mMusic;
    std::map<MusicID, std::string> mFilenames;
    float mVolume;
};

#endif	/* MUSICPLAYER_H */

