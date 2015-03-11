/* 
 * File:   IXMLParser.cpp
 * Author: dorian
 * 
 * Created on 9 de marzo de 2015, 22:55
 */

#include "IXMLParser.h"
#include "XMLParserMap.h"

IXMLParser* IXMLParser::make_parser(TypeParser choice) {
    IXMLParser* parser;
    switch (choice) {
        case TypeParser::MAP:
            parser = new XMLParserMap();
            break;

        case TypeParser::ANIMATION:
        case TypeParser::ENTITY:
        case TypeParser::STATE_MACHINE:
        default:
            parser = new XMLParserMap();
            break;
    };

    return parser;
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

