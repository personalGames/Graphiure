/* 
 * File:   Application.cpp
 * Author: dorian
 * 
 * Created on 28 de diciembre de 2014, 13:23
 */

#include "Application.h"


const sf::Time Application::timePerFrame = sf::seconds(1.f / 60.f);

Application::Application(): window(sf::VideoMode(1024, 768), "Graphiure", sf::Style::Close)
        , textures(), fonts(), stateStack(Context(window, textures, fonts, player))
         {

    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(30);
    
    loadFonts();
    loadTextures();
    
    registerStates();
    stateStack.pushState(StatesID::Title);
    
    hud=new ClockHUD(clock, fonts.get(IDFonts::Main));
    clock.setSampleDepth(100); // Sample 100 frames for averaging.

//    mMusic.setVolume(25.f);
}

void Application::run() {
    
    //sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        // Start a new frame.
        clock.beginFrame();
        
//        sf::Time dt = clock.restart();
//        timeSinceLastUpdate += dt;
//        while (timeSinceLastUpdate > timePerFrame) {
//            timeSinceLastUpdate -= timePerFrame;

            processInput();
            //update(timePerFrame);
            update(clock.getLastFrameTime());
            // Check inside this loop, because stack might be empty before update() call
            if (stateStack.isEmpty())
                window.close();
//        }

        render();
        
        
        // End frame.
        clock.endFrame();
    }
}

void Application::processInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        stateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Application::update(sf::Time dt) {
    stateStack.update(dt);
}

void Application::render() {
    window.clear();
    stateStack.draw();
    window.setView(window.getDefaultView());
    window.draw(*hud);
    window.display();
}

void Application::registerStates() {
    stateStack.registerState<TitleState>(StatesID::Title);
    stateStack.registerState<MenuState>(StatesID::Menu);
    stateStack.registerState<GameState>(StatesID::Game);
    stateStack.registerState<PauseState>(StatesID::Pause);
    stateStack.registerState<LoadingState>(StatesID::Loading);
//    stateStack.registerState<SettingsState>(StatesID::Settings);
//    stateStack.registerState<GameOverState>(StatesID::GameOver);
}

void Application::loadTextures(){
    textures.load(IDTextures::TileSet, "Media/Textures/TileSet.png");
    textures.load(IDTextures::TitleScreen, "Media/Textures/TitleScreen.png");
    textures.load(IDTextures::Buttons, "Media/Textures/Buttons.png");
    textures.load(IDTextures::Player, "Media/Textures/player.png");
}

void Application::loadFonts(){
    fonts.load(IDFonts::Main, "Media/Fonts/Sansation.ttf");
}