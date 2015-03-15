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


class Context {
    
public:

    virtual ~Context();

    Context(sf::RenderWindow& window, ResourceHolder<IDTextures, sf::Texture>& textures,
            ResourceHolder<IDFonts, sf::Font>& fonts, Player& player);


public:
    sf::RenderWindow* window;

    //resources
    ResourceHolder<IDTextures, sf::Texture>* textures;
    ResourceHolder<IDFonts, sf::Font>* fonts;

    //level
    Level* actualLevel;
    Player* player;
};

#endif	/* CONTEXT_H */

