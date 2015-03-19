/* 
 * File:   XMLParserStateMachines.h
 * Author: dorian
 *
 * Created on 13 de marzo de 2015, 10:35
 */

#ifndef XMLPARSERSTATEMACHINES_H
#define	XMLPARSERSTATEMACHINES_H

#include "IXMLParser.h"

class XMLParserStateMachines : public IXMLParser{
public:
    XMLParserStateMachines();
    virtual ~XMLParserStateMachines();
    
    virtual void parse(DataUnion& data, std::string id);
    virtual void parse(DataUnion& data);
private:

};

#endif	/* XMLPARSERSTATEMACHINES_H */

