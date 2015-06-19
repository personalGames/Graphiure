
#include "GameOverState.h"

GameOverState::GameOverState(StateStack& stack, Context* context)
: State(stack, context), mGameOverText(), mElapsedTime(sf::Time::Zero) {

    sf::Font& font = context->fonts->get(IDFonts::Main);
    mGameOverText.setCharacterSize(70);
    mGameOverText.setFont(font);
}

void GameOverState::pushedAction() {
    sf::Vector2f windowSize(context->window->getSize());
    if (context->actualLevel->getMissionStatus() == MissionStatus::MissionFailure) {
        mGameOverText.setString("Mission failed! Pulsa espacio para continuar");
    } else {
        mGameOverText.setString("Mission successful! Pulsa espacio para continuar");
    }
    centerOrigin(mGameOverText);
    mGameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::draw() {
    sf::RenderWindow& window = *getContext()->window;
    window.setView(window.getDefaultView());

    // Create dark, semitransparent background
    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(mGameOverText);
}

bool GameOverState::update(sf::Time dt) {
    return false;
}

bool GameOverState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        requestStateClear();
        requestStackPush(StatesID::Menu);
    }
    return false;
}
