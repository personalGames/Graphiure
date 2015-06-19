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
#include "IDTextures.h"
#include <SFML/Graphics.hpp>
#include <array>
#include "Utilities.h"


class SettingsState : public State {
public:
    SettingsState(StateStack& stack, Context* context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

    virtual void pushedAction();

private:
    void initialize();
    void updateLabels();
    void addButtonLabel(Actions action, float y, const wchar_t* text, Context* context);


private:
    sf::Sprite backgroundSprite;
    GUI::Container GUIContainer;
    std::array<GUI::Button*, Actions::ActionCount> bindingButtons;
    std::array<GUI::Label*, Actions::ActionCount> bindingLabels;
};

#endif	/* SETTINGSTATE_H */

