/* 
 * File:   ConversationState.h
 * Author: dorian
 *
 * Created on 27 de abril de 2015, 20:42
 */

#ifndef CONVERSATIONSTATE_H
#define	CONVERSATIONSTATE_H

#include "SystemObjectsGame.h"
#include "SubStateGame.h"
#include "IdEntity.h"
#include "SystemGraphic.h"
#include <string>
#include "SystemManager.h"

/**
 * Subestado para las conversaciones
 */
class ConversationState : SubStateGame {
public:
    /**
     * Constructor
     * @param id identificador de la entidad que habla
     * @param system gestor de sistemas
     */
    ConversationState(IdEntity id, SystemManager* system);
    virtual ~ConversationState();

    virtual void draw();
    virtual bool update(sf::Time delta);
    virtual bool handleEvent(const sf::Event& event);

private:
    /**
     * Sistema de objetos
     */
    SystemObjectsGame* objects;
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
    sf::String text;
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

