/* 
 * File:   MusicPlayer.cpp
 * Author: dorian
 * 
 * Created on 16 de diciembre de 2014, 11:25
 */

#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(): mMusic(), mFilenames(), mVolume(100.f) {
    mFilenames[MusicID::MenuTheme] = "Media/Music/MenuTheme.ogg";
    mFilenames[MusicID::MissionTheme] = "Media/Music/MissionTheme.ogg";
}

void MusicPlayer::play(MusicID theme) {
    std::string filename = mFilenames[theme];

    if (!mMusic.openFromFile(filename))
        throw std::runtime_error("Music " + filename + " could not be loaded.");

    mMusic.setVolume(mVolume);
    mMusic.setLoop(true);
    mMusic.play();
}

void MusicPlayer::stop() {
    mMusic.stop();
}

void MusicPlayer::setVolume(float volume) {
    mVolume = volume;
}

void MusicPlayer::setPaused(bool paused) {
    if (paused)
        mMusic.pause();
    else
        mMusic.play();
}
