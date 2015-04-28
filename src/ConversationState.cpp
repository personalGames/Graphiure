/* 
 * File:   ConversationState.cpp
 * Author: dorian
 * 
 * Created on 27 de abril de 2015, 20:42
 */

#include "ConversationState.h"
#include "Talk.h"

ConversationState::ConversationState(IdEntity id, SystemManager* system) :
textShown(), marginRectangle(20.f), positionText(0), fontSize(20), textFinish(false), radius(10) {
    objects = static_cast<SystemObjectsGame*>
            (system->getSystem(TypeSystem::OBJECTS));

    graphics = static_cast<SystemGraphic*>
            (system->getSystem(TypeSystem::GRAPHIC));

    Entity* entity = objects->getEntity(id);
    if (entity->HasID("Talk")) {
        Talk* talk = entity->Get<Talk*>("Talk");

        text = *talk->phrase;
    } else {
        text = L"...";
    }

    textShown.setCharacterSize(fontSize);
    font = &(graphics->getFonts().get(IDFonts::Main));
    textShown.setFont(*font);
    marginPhrases = font->getLineSpacing(fontSize);

    sf::RenderTarget& target = graphics->getTarget();
    sf::View view = target.getView();
    sf::Vector2f sizeView = view.getSize();
    sizeRectangle = sizeView;
    sizeRectangle.y = sizeRectangle.y * 0.15;
    //minima altura
    sizeRectangle.y = std::min(sizeRectangle.y, 100.f);
    //maxima altura
    sizeRectangle.y = std::max(sizeRectangle.y, 150.f);

    prepareText();
}

void ConversationState::draw() {
    sf::RenderTarget& target = graphics->getTarget();

    sf::View view = target.getView();
    sf::Vector2f sizeView = view.getSize();
    position = view.getCenter();
    position.x -= (sizeView.x / 2.f);
    position.y = position.y - sizeRectangle.y + (sizeView.y / 2.f);

    

    //dibujar icono para continuar
    sf::CircleShape circle;
    if (!textFinish) {
        circle.setFillColor(sf::Color(200, 150, 0));
        circle.setRadius(10);

        sf::Vector2f positionContinue = position;
        positionContinue.x += sizeView.x - radius*2-(marginRectangle/2);
        positionContinue.y += sizeRectangle.y - radius*2-(marginRectangle/2);
        circle.setPosition(positionContinue);
    }
    
    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sizeRectangle);
    backgroundShape.setPosition(position);

    textShown.setPosition(position.x + marginRectangle, position.y + marginRectangle);

    target.draw(backgroundShape);
    target.draw(circle);
    target.draw(textShown);


}

bool ConversationState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
        setEnded();
    } else if (event.type == sf::Event::KeyPressed) {
        prepareText();
    }
    return true;
}

bool ConversationState::update(sf::Time delta) {
    return true;
}

ConversationState::~ConversationState() {

}

void ConversationState::prepareText() {
    unsigned currentOffset = 0;
    unsigned width = sizeRectangle.x - 2 * marginRectangle;
    unsigned height = sizeRectangle.y - 2 * marginRectangle;
    unsigned totalHeight = 0;
    bool firstWord = true;
    std::size_t wordBegining = 0;
    sf::String result = text.substring(positionText, text.getSize() - positionText);
    bool end = false;
    bool firstLine = true;

    for (std::size_t pos(0); pos < result.getSize() && !end; ++pos) {
        auto currentChar = result[pos];
        if (currentChar == '\n') {
            currentOffset = 0;
            firstWord = true;
            firstLine = true;
            continue;
        } else if (currentChar == ' ') {
            wordBegining = pos;
            firstWord = false;
        }



        auto glyph = font->getGlyph(currentChar, fontSize, false);
        currentOffset += glyph.advance;

        if (firstLine) {
            totalHeight += marginPhrases;
            totalHeight += glyph.bounds.height;
            firstLine = false;
        }

        if (!firstWord && currentOffset > width) {
            pos = wordBegining;
            result[pos] = '\n';
            firstWord = true;
            currentOffset = 0;

        }

        if ((totalHeight + glyph.bounds.height) > height) {
            result = result.substring(0, pos - 1);
            positionText = pos - 1;
            end = true;
        }
    }

    if (!end) {
        textFinish = true;
    }


    //std::wstring phrase = text.toWideString();
    textShown.setString(result);
}

