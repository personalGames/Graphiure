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

class IXMLParser {
public:
    static IXMLParser *make_parser(TypeParser choice);
    
    void setXML(std::string path);
    virtual DataUnion parse(std::string path)=0;
    virtual DataUnion parse(std::string path, std::string id)=0;
    
protected:
    tinyxml2::XMLDocument doc;
};

#endif	/* IXMLPARSER_H */

