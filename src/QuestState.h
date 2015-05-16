/* 
 * File:   ConversationState.h
 * Author: dorian
 *
 * Created on 27 de abril de 2015, 20:42
 */

#ifndef QUESTSTATE_H
#define	QUESTSTATE_H

#include "SystemObjectsGame.h"
#include "SubStateGame.h"
#include "SystemGraphic.h"
#include <string>
#include "SystemManager.h"
#include "SystemQuest.h"

class QuestState : SubStateGame {
public:
    QuestState(SystemManager* system);
    virtual ~QuestState();

    virtual void draw();
    virtual bool update(sf::Time delta);
    virtual bool handleEvent(const sf::Event& event);

private:
    SystemQuest* quest;
    SystemGraphic* graphics;
    sf::Text textShown;
    sf::Vector2f sizeRectangle;
    float marginRectangle;
    float marginPhrases;
    sf::Vector2f position;
    sf::String* text;
    int positionText;
    sf::Font* font;
    unsigned int fontSize;
    bool textFinish;
    float radius;
    
private:
    void prepareText();
};

#endif	/* CONVERSATIONSTATE_H */

