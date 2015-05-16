/* 
 * File:   IXMLParser.cpp
 * Author: dorian
 * 
 * Created on 9 de marzo de 2015, 22:55
 */

#include "IXMLParser.h"
#include "XMLParserMap.h"
#include "XMLParserAnimation.h"
#include "XMLParserStateMachines.h"
#include "XMLParserCollisionsMap.h"
#include "XMLParserCharacter.h"
#include "XMLParserCollisions.h"
#include "XMLParserQuests.h"

IXMLParser* IXMLParser::make_parser(TypeParser choice) {
    IXMLParser* parser;
    switch (choice) {
        case TypeParser::MAP:
            parser = new XMLParserMap();
            break;

        case TypeParser::ANIMATION:
            parser = new XMLParserAnimation();
            break;
        case TypeParser::STATE_MACHINE:
            parser = new XMLParserStateMachines();
            break;

        case TypeParser::COLLISIONS_MAP:
            parser = new XMLParserCollisionsMap();
            break;

        case TypeParser::COLLISIONS:
            parser = new XMLParserCollisions();
            break;

        case TypeParser::CHARACTER:
            parser = new XMLParserCharacter();
            break;
            
        case TypeParser::QUEST:
            parser= new XMLParserQuests();
            break;

        case TypeParser::ENTITY:
        default:
            parser = new XMLParserMap();
            break;
    };

    return parser;
}

void IXMLParser::setResources(ResourceHolder<std::string, sf::Texture>* textures) {
    this->textures = textures;
}

void IXMLParser::setXML(tinyxml2::XMLDocument& path) {
    this->doc = &path;
}

void IXMLParser::setXML(XMLDocument& path) {
    this->doc = path.doc;
}

IXMLParser::~IXMLParser() {

}

