/* 
 * File:   Context.h
 * Author: dorian
 *
 * Created on 28 de diciembre de 2014, 11:48
 */

#ifndef CONTEXT_H
#define	CONTEXT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ResourceHolder.h"
#include "IDFonts.h"
#include "Level.h"
#include "Player.h"
#include "SystemManager.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"
#include <string>

/**
 * Contexto de la aplicación
 */
class Context {
    
public:
    /**
     * Destructor
     */
    virtual ~Context();
    /**
     * Constructor. Todos los parámetros que se le pasan están creados previamente
     * @param window ventana de la aplicación
     * @param textures texturas
     * @param fonts fuentes
     * @param player jugador
     * @param manager gestor de sistemas
     * @param music reproductor de música
     * @param sounds reproductor de sonidos
     * @param name nombre del nivel
     */
    Context(sf::RenderWindow& window, ResourceHolder<std::string, sf::Texture>& textures,
            ResourceHolder<IDFonts, sf::Font>& fonts, Player& player, 
            SystemManager& manager,MusicPlayer& music, SoundPlayer& sounds, std::string& name);


public:
    sf::RenderWindow* window;

    /**
     * Texturas
     */
    ResourceHolder<std::string, sf::Texture>* textures;
    /**
     * Fuentes
     */
    ResourceHolder<IDFonts, sf::Font>* fonts;

    /**
     * Nivel actual del juego
     */
    Level* actualLevel;
    /**
     * Jugador
     */
    Player* player;
    
    /**
     * Sistemas del motor
     */
    SystemManager* systemManager;
    /**
     * Reproductor de música
     */
    MusicPlayer* music;
    /**
     * Reproductor de sonidos
     */
    SoundPlayer* sounds;
    /**
     * Nombre del nivel actual
     */
    std::string* nameLevel;
};

#endif	/* CONTEXT_H */

