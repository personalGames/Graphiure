/* 
 * File:   IXMLParser.h
 * Author: dorian
 *
 * Created on 9 de marzo de 2015, 22:55
 */

#ifndef IXMLPARSER_H
#define	IXMLPARSER_H

#include "TypeParser.h"
#include <string>
#include "../include/tinyxml2.h"
#include "DataUnion.h"
#include <vector>
#include <iostream>
#include "ResourceHolder.h"
#include "XMLDocument.h"

class IXMLParser {
public:
    static IXMLParser *make_parser(TypeParser choice);
    virtual ~IXMLParser();

    
    void setXML(tinyxml2::XMLDocument& path);
    void setXML(XMLDocument& path);
    void setResources(ResourceHolder<std::string, sf::Texture>* textures);
    virtual void parse(DataUnion& data)=0;
    
protected:
    tinyxml2::XMLDocument* doc;
    ResourceHolder<std::string, sf::Texture>* textures;
};

#endif	/* IXMLPARSER_H */

