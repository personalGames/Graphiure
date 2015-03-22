/* 
 * File:   Application.h
 * Author: dorian
 *
 * Created on 28 de diciembre de 2014, 13:23
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceHolder.h"
#include "StateStack.h"
#include "IDFonts.h"
#include "IDTextures.h"
#include "SystemManager.h"

#include "MenuState.h"
#include "TitleState.h"
#include "PauseState.h"
#include "GameState.h"
#include "LoadingState.h"

#include "FrameClock.h"
#include "ClockHUD.h"

class Application {
public:
    Application();
    void run();

private:
    static const sf::Time timePerFrame;
    sf::RenderWindow window;
    ResourceHolder<IDTextures, sf::Texture> textures;
    ResourceHolder<IDFonts, sf::Font> fonts;
    
//    MusicPlayer mMusic;
//    SoundPlayer mSounds;
    
    void processInput();
    void update(sf::Time dt);
    void render();
    void registerStates();

    void loadTextures();
    void loadFonts();
    
    sfx::FrameClock clock;
    ClockHUD* hud;
    
    Player player;
    SystemManager systemManager;
    
    StateStack stateStack;

};

#endif	/* APPLICATION_H */

