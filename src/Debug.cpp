/* 
 * File:   Debug.cpp
 * Author: dorian
 * 
 * Created on 5 de abril de 2015, 18:48
 */

#include "Debug.h"
#include "Collision.h"
#include <iostream>

Debug::Debug(Entity* entity): entity(entity) {
    
}


Debug::~Debug() {
}

void Debug::updateCurrent(sf::Time delta) {
    Collision* col=entity->Get<Collision*>("Debug");
    sf::Transformable t=col->getTransform();
    sf::Vector2f v=t.getPosition();
    setPosition(v);
}

void Debug::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    Collision* col=entity->Get<Collision*>("Debug");
    target.draw(*(col->vertices), states);
}
