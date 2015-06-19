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
#include "IDTextures.h"
#include "IDFonts.h"
#include "Level.h"
#include "Player.h"
#include "SystemManager.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"


class Context {
    
public:

    virtual ~Context();

    Context(sf::RenderWindow& window, ResourceHolder<std::string, sf::Texture>& textures,
            ResourceHolder<IDFonts, sf::Font>& fonts, Player& player, 
            SystemManager& manager,MusicPlayer& music, SoundPlayer& sounds);


public:
    sf::RenderWindow* window;

    //resources
    ResourceHolder<std::string, sf::Texture>* textures;
    ResourceHolder<IDFonts, sf::Font>* fonts;

    //level
    Level* actualLevel;
    Player* player;
    
    //systems
    SystemManager* systemManager;
    
    MusicPlayer* music;
    SoundPlayer* sounds;
};

#endif	/* CONTEXT_H */

