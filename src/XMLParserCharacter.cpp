/* 
 * File:   XMLParserCharacter.cpp
 * Author: dorian
 * 
 * Created on 1 de abril de 2015, 13:40
 */

#include "XMLParserCharacter.h"
#include <iostream>

XMLParserCharacter::XMLParserCharacter() {

}

void XMLParserCharacter::parse(DataUnion& data) {
    PropertyManager* properties = new PropertyManager();
  
    //get first node
    tinyxml2::XMLElement* entity = doc->FirstChildElement("Entity")->FirstChildElement("Properties");
 
    entity = entity->FirstChildElement("Property");

    while (entity) {
        std::string id = entity->Attribute("id");
        if (id.compare("MaxVelocity") == 0) {
            properties->Add<float>("MaxVelocity", entity->FloatAttribute("value"));
        } else if (id.compare("Drawable") == 0) {
            parserAnimations(properties);
        } else if (id.compare("Position") == 0) {
            sf::Vector2f pos=sf::Vector2f(entity->FloatAttribute("x"), entity->FloatAttribute("y"));
            properties->Add<sf::Vector2f>("Position", pos);
        } else if (id.compare("Collision") == 0) {
            parserCollisions(properties);
        } else if (id.compare("Life") == 0) {
            properties->Add<float>("Life", entity->FloatAttribute("value"));
        } else if(id.compare("Talk")==0){
            std::string* chars=new std::string(entity->Attribute("value"));
            properties->Add<std::string*>("Talk", chars);
        }
        entity = entity->NextSiblingElement("Property");
    }

    data.propertiesEntity = properties;

}

XMLParserCharacter::~XMLParserCharacter() {

}

void XMLParserCharacter::parserAnimations(PropertyManager* properties) {
    IXMLParser* parser = IXMLParser::make_parser(TypeParser::STATE_MACHINE);
    parser->setResources(textures);
    parser->setXML(*doc);
    DataUnion data = DataUnion();
    parser->parse(data);
    delete parser;

    StateMachine* state = data.stateMachine;
    parser = IXMLParser::make_parser(TypeParser::ANIMATION);
    parser->setResources(textures);
    parser->setXML(*doc);
    parser->parse(data);
    delete parser;

    StateMachineAnimation* machineAnimation = new StateMachineAnimation(*state);
    machineAnimation->setAnimations(data.animations->animations);
    properties->Add<StateMachineAnimation*>("Drawable", machineAnimation);
    
}

void XMLParserCharacter::parserCollisions(PropertyManager* properties) {
    IXMLParser* parser = IXMLParser::make_parser(TypeParser::COLLISIONS);
    parser->setResources(textures);
    parser->setXML(*doc);
    DataUnion data = DataUnion();
    parser->parse(data);
    delete parser;

    bool pillado = false;
    for (std::vector<StructCollision*>::iterator it = data.collisions->begin();
            it != data.collisions->end(); ++it) {
        //pillo la estructura de esta collision en concreto
        StructCollision* coli = *it;
        if (!pillado) {
            properties->Add<StructCollision*>("Collision", coli);
            pillado = true;
        } else {
            delete *it;
        }
    }
}
