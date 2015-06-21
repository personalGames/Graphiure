/* 
 * File:   XMLParserQuests.h
 * Author: dorian
 *
 * Created on 7 de mayo de 2015, 13:48
 */

#ifndef XMLPARSERQUESTS_H
#define	XMLPARSERQUESTS_H

#include "IXMLParser.h"
#include <string>

/**
 * Parsea el xml con información sobre misiones
 */
class XMLParserQuests : public IXMLParser{
public:
    XMLParserQuests();
    virtual ~XMLParserQuests();
    
    virtual void parse(DataUnion& data);
private:

};

#endif	/* XMLPARSERQUESTS_H */

