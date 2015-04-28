/* 
 * File:   ConversationState.cpp
 * Author: dorian
 * 
 * Created on 27 de abril de 2015, 20:42
 */

#include "ConversationState.h"
#include "Talk.h"

ConversationState::ConversationState(IdEntity id, SystemManager* system): text() {
    objects = static_cast<SystemObjectsGame*>
            (system->getSystem(TypeSystem::OBJECTS));

    graphics = static_cast<SystemGraphic*>
            (system->getSystem(TypeSystem::GRAPHIC));
    
    Entity* entity=objects->getEntity(id);
    if(entity->HasID("Talk")){
        Talk* talk=entity->Get<Talk*>("Talk");
        text.setString(*talk->phrase);
    }else{
        text.setString(L"...");
    }
    
    text.setCharacterSize(20);
    sf::Font& font = graphics->getFonts().get(IDFonts::Main);
    text.setFont(font);
}

void ConversationState::draw() {
    sf::RenderTarget& target=graphics->getTarget();
    
    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sf::Vector2f(300,100));
    backgroundShape.setPosition(target.getView().getCenter());
    text.setPosition(target.getView().getCenter());

    target.draw(backgroundShape);
    target.draw(text);
}

bool ConversationState::handleEvent(const sf::Event& event) {
    return true;
}

bool ConversationState::update(sf::Time delta) {
    return true;
}

ConversationState::~ConversationState() {

}
