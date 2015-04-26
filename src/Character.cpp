/* 
 * File:   Character.cpp
 * Author: dorian
 * 
 * Created on 1 de abril de 2015, 13:28
 */

#include "Character.h"


Character::~Character() {
}

Entity* Character::prepareEntity(PropertyManager& parameters) {
    Entity* entity = new Entity(Category::CHARACTER);

    Velocity* vel = new Velocity();
    vel->setMaxVelocity(parameters.Get<float>("MaxVelocity"));
    entity->Add<Velocity*>("Velocity", vel);
    entity->Add<bool>("Commandable", true);

    Life* life = new Life(parameters.Get<float>("Life"));
    entity->Add<Life*>("Life", life);

    StructCollision* colliStruct=parameters.Get<StructCollision*>("Collision");

    Collision* colli = new Collision();
    sf::Vector2f pos;
    if (parameters.HasID("Position")) {
        pos = parameters.Get<sf::Vector2f>("Position");
        
    } else {
        pos = colliStruct->position;
    }
    
    Position* position = new Position();
    position->updatePosition(pos.x, pos.y);

    sf::Transformable transform = position->getPosition();
    colli->update(transform);
    colli->setArrayVertex(colliStruct->vertices);
    if(parameters.HasID("Ratio")){
        colli->applyRatio(parameters.Get<sf::Vector2f>("Ratio"));
    }
    colli->setType(TypeCollision::DYNAMIC);

    sf::Vector2f offset=colliStruct->position;
    offset.x+=(*colli->vertices)[0].position.x;
    offset.y+=(*colli->vertices)[0].position.y;
    
    position->setPosition(colli->getTransform());

    entity->Add<Position*>("Position", position);
    entity->Add<Collision*>("Collision", colli);
    StateMachineAnimation* animations=parameters.Get<StateMachineAnimation*>("Drawable");
    entity->Add<StateMachineAnimation*>("Drawable", animations);
    
    entity->Add<sf::Vector2f>("OffsetDrawable", offset);

    delete colliStruct;
    
    return entity;
}