/* 
 * File:   PauseState.cpp
 * Author: dorian
 * 
 * Created on 13 de diciembre de 2014, 17:45
 */

#include "PauseState.h"

PauseState::PauseState(StateStack& stack, Context* context)
: State(stack, context)
, pausedText()
, GUIContainer() {
    sf::Font& font = context->fonts->get(IDFonts::Main);
    sf::Vector2f windowSize(context->window->getSize());

    pausedText.setFont(font);
    pausedText.setString(L"Juego pausado");
    pausedText.setCharacterSize(70);
    centerOrigin(pausedText);
    pausedText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

    GUI::Button* returnButton = new GUI::Button(*context);
    returnButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75);
    returnButton->setText(L"Continuar");
    returnButton->setCallback([this] () {
        requestStackPop();
    });

    GUI::Button* settingsButton = new GUI::Button(*context);
    settingsButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125);
    settingsButton->setText(L"Opciones");
    settingsButton->setCallback([this] () {
        requestStackPush(StatesID::Settings);
    });

    GUI::Button* backToMenuButton = new GUI::Button(*context);
    backToMenuButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 175);
    backToMenuButton->setText(L"Volver al menú principal");
    backToMenuButton->setCallback([this] () {
        requestStateClear();
        requestStackPush(StatesID::Menu);
    });

    GUIContainer.pack(returnButton);
    GUIContainer.pack(settingsButton);
    GUIContainer.pack(backToMenuButton);


}

PauseState::~PauseState() {
    getContext()->music->setPaused(false);
}

void PauseState::pulledAction() {
    getContext()->music->setPaused(false);
}

void PauseState::pushedAction() {
    getContext()->music->setPaused(true);
    GUIContainer.clearSelection();
}

void PauseState::draw() {
    sf::RenderWindow& window = *getContext()->window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(pausedText);
    window.draw(GUIContainer);
}

bool PauseState::update(sf::Time) {
    return false;
}

bool PauseState::handleEvent(const sf::Event& event) {
    GUIContainer.handleEvent(event);
    return false;
}