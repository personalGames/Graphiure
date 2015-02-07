/* 
 * File:   LoadingState.cpp
 * Author: dorian
 * 
 * Created on 13 de diciembre de 2014, 17:39
 */

#include "LoadingState.h"

LoadingState::LoadingState(StateStack& stack, Context context)
: State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    sf::Font& font = context.fonts->get(IDFonts::Main);
    sf::Vector2f viewSize = window.getView().getSize();

    loadingText.setFont(font);
    loadingText.setString("Cargando...");
    centerOrigin(loadingText);
    loadingText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f + 50.f);

    progressBarBackground.setFillColor(sf::Color::White);
    progressBarBackground.setSize(sf::Vector2f(viewSize.x - 20, 10));
    progressBarBackground.setPosition(10, loadingText.getPosition().y + 40);

    progressBar.setFillColor(sf::Color(100, 100, 100));
    progressBar.setSize(sf::Vector2f(200, 10));
    progressBar.setPosition(10, loadingText.getPosition().y + 40);

    setCompletion(0.f);

    loadingTask.execute();
}

void LoadingState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(loadingText);
    window.draw(progressBarBackground);
    window.draw(progressBar);
}

bool LoadingState::update(sf::Time) {
    // Update the progress bar from the remote task or finish it
    if (loadingTask.isFinished()) {
        requestStackPop();
        requestStackPush(StatesID::Game);
    } else {
        setCompletion(loadingTask.getCompletion());
    }
    return true;
}

bool LoadingState::handleEvent(const sf::Event& event) {
    return true;
}

void LoadingState::setCompletion(float percent) {
    if (percent > 1.f) // clamp
        percent = 1.f;

    progressBar.setSize(sf::Vector2f(progressBarBackground.getSize().x * percent, progressBar.getSize().y));
}
