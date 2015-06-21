/* 
 * File:   SettingState.h
 * Author: dorian
 *
 * Created on 14 de diciembre de 2014, 1:34
 */

#ifndef SETTINGSTATE_H
#define	SETTINGSTATE_H

#include "StateStack.h"
#include "Actions.h"
#include "Container.h"
#include "Button.h"
#include "Label.h"
#include <SFML/Graphics.hpp>
#include <array>
#include "Utilities.h"

/**
 * Representa la pantalla de opciones. Permite cambiar el mapeo del teclado
 */
class SettingsState : public State {
public:
    /**
     * Constructor
     * @param stack
     * @param context
     */
    SettingsState(StateStack& stack, Context* context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);
    
    virtual void pushedAction();

private:
    /**
     * Inicializa las variables
     */
    void initialize();
    /**
     * Actualiza el texto de las etiquetas
     */
    void updateLabels();
    /**
     * Añade el conjunto de botón y etiqueta asociado a una acción en el contenedor
     * @param action acción asociada
     * @param y altura a la que queda el botón en el contenedor
     * @param text texto del botón
     * @param context contexto de la aplicación
     */
    void addButtonLabel(Actions action, float y, const wchar_t* text, Context* context);


private:
    /**
     * Imagen de fondo
     */
    sf::Sprite backgroundSprite;
    /**
     * Contenedor con los botones de opciones
     */
    GUI::Container GUIContainer;
    /**
     * Vector con todos los botones asociados a acciones
     */
    std::array<GUI::Button*, Actions::ActionCount> bindingButtons;
    /**
     * Vector con todas las etiquetas asociadas a acciones
     */
    std::array<GUI::Label*, Actions::ActionCount> bindingLabels;
};

#endif	/* SETTINGSTATE_H */

