/* 
 * File:   XMLParser.h
 * Author: dorian
 *
 * Created on 12 de febrero de 2015, 16:11
 */

#ifndef XMLPARSER_H
#define	XMLPARSER_H

#include "StructMap.h"
#include <string>
#include "../include/tinyxml2.h"
#include "Utilities.h"
#include <sstream>

class XMLParser {
public:
    XMLParser(std::string path);
    XMLParser(const XMLParser& orig);
    virtual ~XMLParser();

    StructMap* readMap();
    
private:
    tinyxml2::XMLDocument doc;
    

};

#endif	/* XMLPARSER_H */