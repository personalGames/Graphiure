/* 
 * File:   LoadingLevel.cpp
 * Author: dorian
 * 
 * Created on 11 de febrero de 2015, 23:58
 */

#include "LoadingLevel.h"
#include "Entity.h"
#include "AnimatedSprite.h"
#include "IXMLParser.h"
#include "StateMachineAnimation.h"
#include "SystemObjectsGame.h"
#include "SystemGraphic.h"
#include "Velocity.h"
#include "Life.h"
#include "Hole.h"
#include "FactoryGameObjects.h"
#include "XMLDocument.h"
#include "Questeable.h"

LoadingLevel::LoadingLevel(std::string* level, Context* context)
: ParallelTask(), level(level), context(context) {
    levelToLoad = context->actualLevel;
    this->textures = context->textures;
    this->systemManager = context->systemManager;
}

LoadingLevel::~LoadingLevel() {

}

void LoadingLevel::runTask() {
    //compruebo el nivel que tengo que cargar
    {
        sf::Lock lock(mutex);
        completion = 5;
    }

    DataUnion data = DataUnion();


    //preparo los sistemas que necesito
    SystemCollision* collision = static_cast<SystemCollision*> (systemManager->getSystem(TypeSystem::COLLISION));
    SystemGraphic* graphics = static_cast<SystemGraphic*> (systemManager->getSystem(TypeSystem::GRAPHIC));
    SystemQuest* quests = static_cast<SystemQuest*> (systemManager->getSystem(TypeSystem::QUEST));
    //y por último el sistema de objetos
    SystemObjectsGame* objectsGame = static_cast<SystemObjectsGame*> (systemManager->getSystem(TypeSystem::OBJECTS));

    level=context->nameLevel;
    XMLDocument document = XMLDocument("Media/Levels/" + *level);
    std::cout<<*level<<std::endl;
    //recojo el xml del nivel
    IXMLParser* parser = IXMLParser::make_parser(TypeParser::MAP);
    parser->setResources(textures);
    parser->setXML(document);
    //parseo el nivel
    parser->parse(data);
    delete parser;
    StructMap* infoMap = data.map;
    {
        sf::Lock lock(mutex);
        completion = 10;
    }

    //pass the information to build the scene with all this data readed
    graphics->newScene(infoMap);
    collision->newWorldCollision(graphics->getBounds());
    delete infoMap;

    {
        sf::Lock lock(mutex);
        completion = 35;
    }

    // leo las colisiones del mapa 
    Entity* colisionable;
    parser = IXMLParser::make_parser(TypeParser::COLLISIONS_MAP);
    parser->setXML(document);
    parser->parse(data);
    delete parser;

    PropertyManager parameters;
    //la posición hay que ajustarla al tamaño modificado del mapa
    //se saca el factor del mapa y se aplica
    sf::Vector2f ratio = graphics->getRatio();
    for (std::vector<StructCollision*>::iterator it = data.collisions->begin();
            it != data.collisions->end(); ++it) {
        //pillo la estructura de esta collision en concreto
        StructCollision* coli = *it;
        //guardo los datos que se necesitarán para construir el objeto
        parameters = PropertyManager();
        parameters.Add<sf::Vector2f>("Ratio", ratio);
        parameters.Add<sf::Vector2f>("Position", coli->position);
        parameters.Add<sf::VertexArray*>("Vertex", coli->vertices);
        if (coli->data != nullptr) {
            parameters.Add<std::string*>("Level", coli->data);
        }

        //preparo el factory que creará el entity
        std::unique_ptr<GameObjects> gameObject = FactoryGameObjects::getFactory(coli->typeCollision);
        //creo el entity
        colisionable = gameObject->prepareEntity(parameters);

        //registro el entity y los subsistemas lo recogerán si es de su incumbencia
        objectsGame->registerEntity(colisionable);
        delete *it;
    }

    {
        sf::Lock lock(mutex);
        completion = 40;
    }

    //ahora vienen los personajes del nivel
    parser = IXMLParser::make_parser(TypeParser::PEOPLE);
    parser->setResources(textures);
    parser->setXML(document);
    //parseo el nivel
    parser->parse(data);
    delete parser;
    StructPeople* infoPeople = data.people;

    parser = IXMLParser::make_parser(TypeParser::CHARACTER);
    document.load("Media/Data/" + *(infoPeople->character));
    parser->setXML(document);
    parser->setResources(textures);
    parser->parse(data);
    delete parser;
    std::unique_ptr<GameObjects> gameObject = FactoryGameObjects::getFactory("Character");
    Entity* character = gameObject->prepareEntity(*data.propertiesEntity);

    delete data.propertiesEntity;


    levelToLoad->setCharacter(character->getId());
    {
        sf::Lock lock(mutex);
        completion = 55;
    }

    //he terminado con mi personaje, lo registro/guardo
    objectsGame->registerEntity(character);


    //parseo los personajes del nivel
    std::vector<std::string*> villagers = *(infoPeople->villagers);
    for (uint i = 0; i < villagers.size(); ++i) {
        parser = IXMLParser::make_parser(TypeParser::CHARACTER);
        std::string* name = villagers.at(i);
        document.load("Media/Data/" + *name);
        parser->setXML(document);
        parser->setResources(textures);
        parser->parse(data);
        delete parser;
        gameObject = FactoryGameObjects::getFactory("Villager");
        character = gameObject->prepareEntity(*data.propertiesEntity);

        delete data.propertiesEntity;
        objectsGame->registerEntity(character);
    }


    {
        sf::Lock lock(mutex);
        completion = 70;
    }

    parser = IXMLParser::make_parser(TypeParser::QUEST);
    document.load("Media/Data/Quests.xml");
    parser->setXML(document);

    parser->parse(data);
    delete parser;

    std::vector<Quest*>* questsData = data.quests;
    Questeable* questeable;
    for (std::vector<Quest*>::iterator it = questsData->begin(); it != questsData->end(); ++it) {
        Quest* quest = *it;
        quest->setOpened(true);

        //a los entities implicados, les añado su partquest asociado
        const std::vector<PartQuest*> parts = quest->getPartQuests();
        for (std::vector<PartQuest*>::const_iterator it = parts.begin(); it != parts.end(); ++it) {
            IdEntity idCharacter = (*it)->getIdDestiny();
            character = objectsGame->getEntityXml(idCharacter);

            if (!character->HasID("Questeable")) {
                questeable = new Questeable(quest->getId());
                //registro los entities questeables
                quests->registerEntity(character);
                character->Add<Questeable*>("Questeable", questeable);
            } else {
                questeable = character->Get<Questeable*>("Questeable");

            }
            questeable->addPartQuest(*it);
            character->Set<Questeable*>("Questeable", questeable);
        }


        //guardo el quest en el sistema
        quests->addQuest(quest);
    }

    { // finished may be accessed from multiple threads, protect it
        sf::Lock lock(mutex);
        completion = 100;
        finished = true;
    }
}