/* 
 * File:   Container.cpp
 * Author: dorian
 * 
 * Created on 13 de diciembre de 2014, 19:41
 */

#include "Container.h"

namespace GUI {

    Container::Container() : children(), selectedChild(-1) {

    }

    void Container::pack(Component* component) {
        children.push_back(component);

    }

    void Container::clearSelection() {
        if(hasSelection()){
            children[selectedChild]->deselect();
        }
        selectedChild = -1;
    }

    bool Container::isSelectable() const {
        return false;
    }

    void Container::handleEvent(const sf::Event& event) {
        //If we have selected a child then give it events
        if (hasSelection() && children[selectedChild]->isActive()) {
            children[selectedChild]->handleEvent(event);

        } else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                selectPrevious();
            } else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                selectNext();
            } else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) {
                if (hasSelection())
                    children[selectedChild]->activate();
            }
        }
    }

    void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();

        for (const Component* child : children) {
            target.draw(*child, states);
        }
    }

    bool Container::hasSelection() const {
        return selectedChild >= 0;
    }

    void Container::select(std::size_t index) {
        if (children[index]->isSelectable()) {
            if (hasSelection())
                children[selectedChild]->deselect();

            children[index]->select();
            selectedChild = index;
        }
    }

    void Container::selectNext() {
        if (!hasSelection()) {
            if (children.size() > 0) {
                int index = 0;
                select(index);
            }
        } else {

            // Search next component that is selectable, wrap around if necessary
            int next = selectedChild;
            do {
                next = (next + 1) % children.size();
            } while (!children[next]->isSelectable());

            // Select that component
            select(next);
        }
    }

    void Container::selectPrevious() {
        if (!hasSelection()) {
            int index = children.size() - 1;
            if (index >= 0) {
                select(index);
            }
        } else {

            // Search previous component that is selectable, wrap around if necessary
            int prev = selectedChild;
            do {
                prev = (prev + children.size() - 1) % children.size();
            } while (!children[prev]->isSelectable());

            // Select that component
            select(prev);
        }
    }

    Container::~Container() {

    }


}