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

/**
 * Reproductor de música
 */
class MusicPlayer : private sf::NonCopyable {
public:
    /**
     * Constructor
     */
    MusicPlayer();
    /**
     * Reproduce la música del identificador dado
     * @param theme identificador de la música
     */
    void play(MusicID theme);
    /**
     * Para la música
     */
    void stop();
    /**
     * Pausa o no la música
     * @param paused true si se quiere pausar la música
     */
    void setPaused(bool paused);
    /**
     * Establece un volumen para la música
     * @param volume
     */
    void setVolume(float volume);


private:
    /**
     * Música a reproducir
     */
    sf::Music mMusic;
    /**
     * Mapeo entre los identificadores de la música y el fichero asociado
     */
    std::map<MusicID, std::string> mFilenames;
    /**
     * VOlumen de la música
     */
    float mVolume;
};

#endif	/* MUSICPLAYER_H */

