/* 
 * File:   XMLParserCollisionsMap.h
 * Author: dorian
 *
 * Created on 19 de marzo de 2015, 12:36
 */

#ifndef XMLPARSERCOLLISIONSMAP_H
#define	XMLPARSERCOLLISIONSMAP_H

#include "IXMLParser.h"
#include "Collision.h"
#include "DataUnion.h"
#include <vector>
#include <string>

class XMLParserCollisionsMap : public IXMLParser {
public:
    XMLParserCollisionsMap();
    virtual ~XMLParserCollisionsMap();
    

    virtual void parse(DataUnion& data);
    
private:
    
};

#endif	/* XMLPARSERCOLLISIONSMAP_H */

