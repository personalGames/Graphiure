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
#include <sstream>
#include "../include/tinyxml2.h"
#include "DataUnion.h"
#include <vector>
#include <iostream>
#include "Utilities.h"
#include "ResourceHolder.h"
#include "IDTextures.h"

class IXMLParser {
public:
    static IXMLParser *make_parser(TypeParser choice);
    virtual ~IXMLParser();

    
    void setXML(std::string path);
    void setResources(ResourceHolder<IDTextures, sf::Texture>* textures);
    virtual void parse(DataUnion& data)=0;
    virtual void parse(DataUnion& data, std::string id)=0;
    
protected:
    tinyxml2::XMLDocument doc;
    ResourceHolder<IDTextures, sf::Texture>* textures;
};

#endif	/* IXMLPARSER_H */

