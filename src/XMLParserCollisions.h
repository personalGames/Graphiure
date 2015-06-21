/* 
 * File:   XMLParserCollisions.h
 * Author: dorian
 *
 * Created on 1 de abril de 2015, 14:01
 */

#ifndef XMLPARSERCOLLISIONS_H
#define	XMLPARSERCOLLISIONS_H

#include "IXMLParser.h"
#include "Collision.h"
#include "DataUnion.h"
#include <vector>
#include <string>

/**
 * Parsea el xml con información sobre colisiones
 */
class XMLParserCollisions : public IXMLParser{
public:
    XMLParserCollisions();
    virtual ~XMLParserCollisions();
    
    virtual void parse(DataUnion& data);
private:

};

#endif	/* XMLPARSERCOLLISIONS_H */

