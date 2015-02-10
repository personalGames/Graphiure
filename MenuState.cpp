/* 
 * File:   MenuState.cpp
 * Author: dorian
 * 
 * Created on 13 de diciembre de 2014, 17:44
 */

#include "MenuState.h"

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context), container() {


    sf::Texture& texture = context.textures->get(IDTextures::TitleScreen);
    backgroundSprite.setTexture(texture);
    
//    context.music->play(MusicID::MenuTheme);

    GUI::Button* playButton = new GUI::Button(context);
    playButton->setPosition(100, 300);
    playButton->setText(L"Nueva partida");
    playButton->setCallback([this]() {
        requestStackPop();
        requestStackPush(StatesID::Game);
    });
    
    GUI::Button* loadButton = new GUI::Button(context);
    loadButton->setPosition(100, 350);
    loadButton->setText(L"Cargar partida");
    loadButton->setCallback([this]() {
        requestStackPop();
        requestStackPush(StatesID::Game);
    });

    GUI::Button* settingsButton = new GUI::Button(context);
    settingsButton->setPosition(100, 400);
    settingsButton->setText(L"Opciones");
    settingsButton->setCallback([this] () {
        requestStackPush(StatesID::Settings);
    });

    GUI::Button* exitButton = new GUI::Button(context);
    exitButton->setPosition(100, 450);
    exitButton->setText(L"Salir");
    exitButton->setCallback([this] () {
        requestStackPop();
    });
    

    container.pack(playButton);
    container.pack(loadButton);
    container.pack(settingsButton);
    container.pack(exitButton);

}

void MenuState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(backgroundSprite);
    window.draw(container);
}

bool MenuState::update(sf::Time) {
    return true;
}

bool MenuState::handleEvent(const sf::Event& event) {
    container.handleEvent(event);
    return false;
}