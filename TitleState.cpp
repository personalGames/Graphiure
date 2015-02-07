/* 
 * File:   TitleScreen.cpp
 * Author: dorian
 * 
 * Created on 28 de diciembre de 2014, 12:18
 */

#include "TitleState.h"

TitleState::TitleState(StateStack& stack, Context context): State(stack, context),
        text(), showText(true), textEffectTime(sf::Time::Zero) {
    
    backgroundSprite.setTexture(context.textures->get(IDTextures::TitleScreen));

    text.setFont(context.fonts->get(IDFonts::Main));
    text.setString("Press any key to start");
    centerOrigin(text);
    text.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(backgroundSprite);
    sf::View view=window.getView();
    view.setSize(1024.f,768.f);
    window.setView(view);
    if (showText){
        window.draw(text);
    }
}

bool TitleState::update(sf::Time delta) {
    textEffectTime += delta;

    if (textEffectTime >= sf::seconds(0.5f)) {
        showText = !showText;
        textEffectTime = sf::Time::Zero;
    }

    return true;
}

bool TitleState::handleEvent(const sf::Event& event) {
    // If any key is pressed, trigger the next screen
    if (event.type == sf::Event::KeyPressed) {
        requestStackPop();
        requestStackPush(StatesID::Menu);
    }

    return true;
}