/* 
 * File:   XMLParserAnimation.h
 * Author: dorian
 *
 * Created on 11 de marzo de 2015, 11:08
 */

#ifndef XMLPARSERANIMATION_H
#define	XMLPARSERANIMATION_H

#include "IXMLParser.h"

/**
 * Parsea un xml con información sobre animaciones
 */
class XMLParserAnimation : public IXMLParser {
public:
    XMLParserAnimation();
    virtual ~XMLParserAnimation();
    
    virtual void parse(DataUnion& data);
    
private:
    void storeFrames(std::string image, tinyxml2::XMLElement* node, StructAnimation* animation, bool replay, bool wait);
};

#endif	/* XMLPARSERANIMATION_H */

