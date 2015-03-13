/* 
 * File:   Context.cpp
 * Author: dorian
 * 
 * Created on 28 de diciembre de 2014, 11:48
 */

#include "Context.h"

Context::Context(sf::RenderWindow& window, ResourceHolder<IDTextures, sf::Texture>& textures,
        ResourceHolder<IDFonts, sf::Font>& fonts, Player& player): window(&window), textures(&textures),
        fonts(&fonts), actualLevel(nullptr), player(&player) {

}

Context::~Context() {

}