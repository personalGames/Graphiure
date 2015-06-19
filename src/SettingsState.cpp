/* 
 * File:   SettingState.cpp
 * Author: dorian
 * 
 * Created on 14 de diciembre de 2014, 1:34
 */

#include "SettingsState.h"
#include "Actions.h"
#include "IDTextures.h"

SettingsState::SettingsState(StateStack& stack, Context* context) : State(stack, context), GUIContainer() {
    backgroundSprite.setTexture(context->textures->get("TitleScreen.png"));

    initialize();

    // Build key binding buttons and labels
    addButtonLabel(Actions::Left, 150.f, L"Mover izquierda", context);
    addButtonLabel(Actions::Right, 200.f, L"Mover derecha", context);
    addButtonLabel(Actions::Up, 250.f, L"Mover arriba", context);
    addButtonLabel(Actions::Down, 300.f, L"Mover abajo", context);
    addButtonLabel(Actions::Attack, 370.f, L"Atacar", context);
    addButtonLabel(Actions::ActionQuest, 420.f, L"Ver misiones", context);
    addButtonLabel(Actions::ActionPlayer, 470.f, L"Acción", context);



    auto backButton = new GUI::Button(*context);
    backButton->setPosition(80.f, 570.f);
    backButton->setText(L"Volver");
    backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

    GUIContainer.pack(backButton);
}

void SettingsState::pushedAction() {
    updateLabels();
}

void SettingsState::draw() {
    sf::RenderWindow& window = *getContext()->window;

    window.draw(backgroundSprite);
    window.draw(GUIContainer);
}

bool SettingsState::update(sf::Time) {
    return true;
}

bool SettingsState::handleEvent(const sf::Event& event) {
    bool isKeyBinding = false;

    // Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
    for (std::size_t action = 0; action < Actions::ActionCount; ++action) {
        if (bindingButtons[action] != nullptr) {
            if (bindingButtons[action]->isActive()) {
                isKeyBinding = true;
                if (event.type == sf::Event::KeyReleased) {
                    getContext()->player->assignKey(static_cast<Actions> (action), event.key.code);
                    bindingButtons[action]->deactivate();
                }
                break;
            }
        }
    }

    // If pressed button changed key bindings, update labels; otherwise consider other buttons in container
    if (isKeyBinding) {
        updateLabels();
    } else {
        GUIContainer.handleEvent(event);
    }
    return false;
}

void SettingsState::initialize() {
    for (std::size_t i = 0; i < Actions::ActionCount; ++i) {
        bindingLabels[i] = nullptr;
        bindingButtons[i] = nullptr;
    }
}

void SettingsState::updateLabels() {
    Player& player = *getContext()->player;

    for (std::size_t i = 0; i < Actions::ActionCount; ++i) {
        sf::Keyboard::Key key = player.getAssignedKey(static_cast<Actions> (i));
        if (bindingLabels[i] != nullptr) {
            
            bindingLabels[i]->setText(toString(key));
        }
    }
}

void SettingsState::addButtonLabel(Actions action, float y, const wchar_t* text, Context* context) {
    bindingButtons[action] = new GUI::Button(*context);
    bindingButtons[action]->setPosition(80.f, y);
    bindingButtons[action]->setText(text);
    bindingButtons[action]->setToggle(true);

    bindingLabels[action] = new GUI::Label(L"", *context->fonts);
    bindingLabels[action]->setPosition(300.f, y + 15.f);

    GUIContainer.pack(bindingButtons[action]);
    GUIContainer.pack(bindingLabels[action]);
}
