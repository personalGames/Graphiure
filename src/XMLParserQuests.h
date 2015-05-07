/* 
 * File:   XMLParserQuests.h
 * Author: dorian
 *
 * Created on 7 de mayo de 2015, 13:48
 */

#ifndef XMLPARSERQUESTS_H
#define	XMLPARSERQUESTS_H

#include "IXMLParser.h"

class XMLParserQuests : public IXMLParser{
public:
    XMLParserQuests();
    virtual ~XMLParserQuests();
    
    virtual void parse(DataUnion& data);
private:

};

#endif	/* XMLPARSERQUESTS_H */

