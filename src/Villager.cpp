/* 
 * File:   Villager.cpp
 * Author: dorian
 * 
 * Created on 1 de abril de 2015, 17:46
 */

#include "Villager.h"
#include "Subject.h"
#include "Quest.h"
#include "Questeable.h"
#include "ActionStack.h"

Villager::Villager() {
}

Entity* Villager::prepareEntity(PropertyManager& parameters) {
    Entity* entity = new Entity(Category::CHARACTER);

    if (parameters.HasID("idXML")) {
        IdEntity id = IdEntity(parameters.Get<int>("idXML"));
        entity->setIdXml(id);
    }

    if (parameters.HasID("MaxVelocity")) {
        Velocity* vel = new Velocity();
        vel->setMaxVelocity(parameters.Get<float>("MaxVelocity"));
        entity->Add<Velocity*>("Velocity", vel);
    }

    //entity->Add<bool>("Commandable", true);

    if (parameters.HasID("Life")) {
        Life* life = new Life(parameters.Get<float>("Life"));
        entity->Add<Life*>("Life", life);
    }

    Position* position = new Position();
    sf::Vector2f pos;
    if (parameters.HasID("Position")) {
        pos = parameters.Get<sf::Vector2f>("Position");
        position->updatePosition(pos.x, pos.y);
    }


    if (parameters.HasID("Collision")) {
        StructCollision* colliStruct = parameters.Get<StructCollision*>("Collision");

        Collision* colli = new Collision();
        if (!parameters.HasID("Position")) {
            pos = colliStruct->position;
            position->updatePosition(pos.x, pos.y);
        }

        sf::Transformable transform = position->getPosition();
        colli->update(transform);
        colli->setArrayVertex(colliStruct->vertices);
        if (parameters.HasID("Ratio")) {
            colli->applyRatio(parameters.Get<sf::Vector2f>("Ratio"));
        }
        colli->setType(TypeCollision::STATIC);
        position->setPosition(colli->getTransform());

        delete colliStruct;
        entity->Add<Collision*>("Collision", colli);
    }

    entity->Add<Position*>("Position", position);


    if (parameters.HasID("Drawable")) {
        StateMachineAnimation* animations = parameters.Get<StateMachineAnimation*>("Drawable");
        entity->Add<StateMachineAnimation*>("Drawable", animations);
    }

    if (parameters.HasID("query")) {
        sf::Vector2f size = parameters.Get<sf::Vector2f>("query");
        entity->Add<sf::Vector2f>("query", size);
    }

    if (parameters.HasID("Talk")) {
        Talk* talk = new Talk(parameters.Get<sf::String*>("Talk"));
        entity->Add<Talk*>("Talk", talk);
    }

    OnCollision* onCollision = new OnCollision();
    makeOnCollision(entity->getId(), onCollision);
    entity->Add<OnCollision*>("OnCollision", onCollision);

    Behaviour* behaviour = new Behaviour();
    makeBehaviour(behaviour, entity);
    entity->Add<Behaviour*>("Behaviour", behaviour);

    return entity;
}

void Villager::makeOnCollision(IdEntity idObject, OnCollision* onCollision) {
    auto aFunction = [idObject] (MessageCollision * message) {

        Entity* moveEntity = message->entityTwo;
        if (moveEntity->getId() == idObject) {
            moveEntity = message->entityOne;
        }

        double x, y;
        x = message->mtv.pushX;
        y = message->mtv.pushY;
        if (message->axisX)

            if (abs(x) < 0.1) {
                x = 0;
            }

        if (abs(y) < 0.1) {
            y = 0;
        }
        std::cout << x << " " << y << std::endl;
        moveEntity->Get<Position*>("Position")->setPositionIncrement(x, y);
    };

    //guardo la función creada
    onCollision->onCollisionFunction = aFunction;
}

void Villager::makeBehaviour(Behaviour* behaviour, Entity* entity) {
    auto function = [this, entity] (Actions action, PropertyManager * prop) {
        switch (action) {
            case Actions::ActionPlayer:
            {
                if (entity->HasID("Talk")) {
                    Subject* sub = entity->Get<Subject*>("messageEntities");
                    Message m = Message();
                    m.setState(GameStates::CONVERSATION);
                    m.setIdEntity(entity->getId());
                    

                    sub->setMessage(m);
                }
                break;
            }
            case Actions::ActionQuest:
            {
                Subject* sub = entity->Get<Subject*>("messageEntities");
                Message m = Message();
                m.setState(GameStates::QUEST);

                sub->setMessage(m);
                break;
            }

            case Actions::Attack:
            {
                if (entity->HasID("Life")) {
                    //hacer daño
                    Life* life = entity->Get<Life*>("Life");
                    int damage = prop->Get<int>("damage");
                    life->damage(damage);
                    if (!life->isAlive()) {
                        entity->Get<StateMachineAnimation*>("Drawable")->update(Actions::Dead);
                    }
                }
                break;
            }

            default:
                break;
        }

        //don't mind the action or if has a reaction, but notify the partquest
        if (entity->HasID("Questeable")) {
            Questeable* quest = entity->Get<Questeable*>("Questeable");
            processQuest(quest, entity, action);
        }
    };

    behaviour->behaviourFunction = function;
}

void Villager::processQuest(Questeable* quest, Entity* entity, Actions action) {
    const std::vector<PartQuest*> list = quest->getPartQuest();
    for (std::vector<PartQuest*>::const_iterator it = list.begin(); it != list.end(); ++it) {
        PartQuest* part = *it;
        TypeQuest type = part->getType();
        switch (type) {
            case TypeQuest::KILL:
            {
                if (entity->HasID("Life")) {
                    Life* life = entity->Get<Life*>("Life");
                    if (!life->isAlive()) {
                        part->setDone(true);
                    }
                }
                break;
            }

            case TypeQuest::ACTION:
            {
                if (action == part->getAction()) {
                    part->setDone(true);
                }
                break;
            }

            case TypeQuest::TALK:
            {
                if (action == Actions::ActionPlayer) {
                    part->setDone(true);
                }
                break;
            }

            case TypeQuest::CARRY:
            {
                break;
            }

            default:
                break;
        }

    }
}
