/* 
 * File:   Component.cpp
 * Author: dorian
 * 
 * Created on 13 de diciembre de 2014, 19:41
 */

#include "Component.h"

namespace GUI {

    Component::Component() : selected(false), actived(false) {
    }

    Component::~Component() {
    }

    bool Component::isSelected() const {
        return selected;
    }

    void Component::select() {
        selected = true;
    }

    void Component::deselect() {
        selected = false;
    }

    bool Component::isActive() const {
        return actived;
    }

    void Component::activate() {
        actived = true;
    }

    void Component::deactivate() {
        actived = false;
    }

}
