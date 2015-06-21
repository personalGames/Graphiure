/* 
 * File:   XMLParserPeople.h
 * Author: dorian
 *
 * Created on 20 de junio de 2015, 21:51
 */

#ifndef XMLPARSERPEOPLE_H
#define	XMLPARSERPEOPLE_H

#include "IXMLParser.h"


/**
 * Parsea el xml con información sobre entidades que hay en un mapa
 */
class XMLParserPeople : public IXMLParser {
public:
    XMLParserPeople();
    virtual ~XMLParserPeople();
    

    virtual void parse(DataUnion& data, std::string id);
    virtual void parse(DataUnion& data);

    
private:
};

#endif	/* XMLPARSERPEOPLE_H */

