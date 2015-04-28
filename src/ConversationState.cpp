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
        std::wstring phrase=(talk->phrase->fromUtf8(talk->phrase->begin(), talk->phrase->end())).toWideString();
        text.setString(phrase);
    }else{
        text.setString(L"...");
    }
    
    text.setCharacterSize(20);
    sf::Font& font = graphics->getFonts().get(IDFonts::Main);
    text.setFont(font);
}

void ConversationState::draw() {
    sf::RenderTarget& target=graphics->getTarget();
    sf::View view=target.getView();
    sf::Vector2f sizeView=view.getSize();
    sf::Vector2f sizeRectangle=sizeView;
    sizeRectangle.y=sizeRectangle.y*0.15;
    //minima altura
    sizeRectangle.y=std::min(sizeRectangle.y, 100.f);
    //maxima altura
    sizeRectangle.y=std::max(sizeRectangle.y, 150.f);
    
    sf::Vector2f position=target.getView().getCenter();
    position.x-=(sizeView.x/2.f);
    position.y=position.y-sizeRectangle.y+(sizeView.y/2.f);
    
    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sizeRectangle);
    backgroundShape.setPosition(position);
    
    position.x+=20.f;
    position.y+=20.f;
    text.setPosition(position);

    target.draw(backgroundShape);
    target.draw(text);
}

bool ConversationState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
        setEnded();
    }
    return true;
}

bool ConversationState::update(sf::Time delta) {
    return true;
}

ConversationState::~ConversationState() {

}
