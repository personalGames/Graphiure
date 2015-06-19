/* 
 * File:   Context.cpp
 * Author: dorian
 * 
 * Created on 28 de diciembre de 2014, 11:48
 */

#include "Context.h"

Context::Context(sf::RenderWindow& window, ResourceHolder<std::string, sf::Texture>& textures,
        ResourceHolder<IDFonts, sf::Font>& fonts, Player& player,SystemManager& manager,
        MusicPlayer& music, SoundPlayer& sounds): 
        window(&window), textures(&textures), fonts(&fonts), actualLevel(nullptr), 
        player(&player), systemManager(&manager), music(&music), sounds(&sounds) {

}

Context::~Context() {

}