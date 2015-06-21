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

/**
 * Subestado para las misiones
 */
class QuestState : SubStateGame {
public:
    /**
     * Constructor
     * @param system gestor de sistemas
     */
    QuestState(SystemManager* system);
    virtual ~QuestState();

    virtual void draw();
    virtual bool update(sf::Time delta);
    virtual bool handleEvent(const sf::Event& event);

private:
    /**
     * SIstema de misiones
     */
    SystemQuest* quest;
    /**
     * Sistema de gráficos
     */
    SystemGraphic* graphics;
    /**
     * Texto a visualizar
     */
    sf::Text textShown;
    /**
     * Tamaño del rectángulo donde se escribe
     */
    sf::Vector2f sizeRectangle;
    /**
     * Margen del rectángulo
     */
    float marginRectangle;
    /**
     * Margen de las frases
     */
    float marginPhrases;
    /**
     * Posición del texto
     */
    sf::Vector2f position;
    /**
     * Texto total que se visualizará
     */
    sf::String* text;
    /**
     * Posición del texto
     */
    int positionText;
    /**
     * Fuente del texto
     */
    sf::Font* font;
    /**
     * Tamaño de la fuente
     */
    unsigned int fontSize;
    /**
     * Si el texto ha finalizado
     */
    bool textFinish;
    /**
     * Radio de la imagen para continuar el texto
     */
    float radius;
    
private:
    /**
     * Prepara el texto que se va a mostrar por pantalla
     */
    void prepareText();
};

#endif	/* CONVERSATIONSTATE_H */

