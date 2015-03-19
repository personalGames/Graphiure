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
            
        case TypeParser::COLLISIONS:
            parser=new XMLParserCollisionsMap();
            break;

        case TypeParser::ENTITY:
        default:
            parser = new XMLParserMap();
            break;
    };

    return parser;
}

void IXMLParser::setResources(ResourceHolder<IDTextures, sf::Texture>* textures) {
    this->textures = textures;
}

void IXMLParser::setXML(std::string path) {
    std::vector<char> writable = *convertString(path);

    doc.LoadFile(&writable[0]);
    if (doc.ErrorID() != 0) {
        std::cout << "Error: " << doc.ErrorID() << " - " << doc.ErrorName() << std::endl;
    }

    //delete the created vector
    deleteVector(writable);
}

IXMLParser::~IXMLParser() {

}

