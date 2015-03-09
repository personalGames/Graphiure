/* 
 * File:   XMLParserMap.h
 * Author: dorian
 *
 * Created on 9 de marzo de 2015, 23:03
 */

#ifndef XMLPARSERMAP_H
#define	XMLPARSERMAP_H

#include "IXMLParser.h"
#include "StructMap.h"


class XMLParserMap : public IXMLParser {
public:
    XMLParserMap();
    virtual ~XMLParserMap();
    

    virtual DataUnion parse(std::string id);
    virtual DataUnion parse();

    
private:
    void parseBackground(StructMap* result, tinyxml2::XMLElement* layer);
    void parseUnderground(StructMap* result, tinyxml2::XMLElement* layer);
};

#endif	/* XMLPARSERMAP_H */

