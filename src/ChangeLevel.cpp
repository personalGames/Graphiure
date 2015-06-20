/* 
 * File:   ChangeLevel.cpp
 * Author: dorian
 * 
 * Created on 20 de junio de 2015, 16:29
 */

#include "ChangeLevel.h"

#include "Velocity.h"
#include "Life.h"
#include "StateMachineAnimation.h"

Entity* ChangeLevel::prepareEntity(PropertyManager& parameters) {
    Entity* entity = new Entity();

    Collision* colli = new Collision();
    sf::Vector2f pos = parameters.Get<sf::Vector2f>("Position");
    Position* position = new Position();
    position->updatePosition(pos.x, pos.y);

    sf::Transformable transform = position->getPosition();
    colli->update(transform);
    colli->setArrayVertex(parameters.Get<sf::VertexArray*>("Vertex"));
    colli->applyRatio(parameters.Get<sf::Vector2f>("Ratio"));
    colli->setType(TypeCollision::STATIC);

    position->setPosition(colli->getTransform());

    entity->Add<Position*>("Position", position);
    entity->Add<Collision*>("Collision", colli);
    
    std::string* level=parameters.Get<std::string*>("Level");
    entity->Add<std::string*>("Level", level);

    entity->Add<Collision*>("Debug", colli);

    OnCollision* onCollision = new OnCollision();
    makeOnCollision(entity->getId(), onCollision);
    entity->Add<OnCollision*>("OnCollision", onCollision);

    return entity;
}

void ChangeLevel::makeOnCollision(IdEntity idObject, OnCollision* onCollision) {
    auto aFunction = [idObject] (MessageCollision * message) {
        Entity* other = message->entityOne;
        if (other->getId() == idObject) {
            other = message->entityTwo;
        }
        //cambiamos el nivel usando los mensajes
        Subject* sub = other->Get<Subject*>("messageEntities");
        Message m = Message();
        std::string* level=message->entityOne->Get<std::string*>("Level");
        m.setData(level);
        m.setState(GameStates::CHANGE_LEVEL);

        sub->setMessage(m);
    };

    //guardo la función creada
    onCollision->onCollisionFunction = aFunction;

}

ChangeLevel::~ChangeLevel() {
}

