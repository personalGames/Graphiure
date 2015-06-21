/* 
 * File:   XMLDocument.h
 * Author: dorian
 *
 * Created on 1 de abril de 2015, 13:33
 */

#ifndef XMLDOCUMENT_H
#define	XMLDOCUMENT_H

#include "../include/tinyxml2.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "Utilities.h"

/**

 * Clase que guarda la ruta y carga el xml indicado.
 * Mantiene una referencia al documento xml
 */
class XMLDocument {
public:
    XMLDocument(std::string path);
    virtual ~XMLDocument();
    
    void load(std::string path);
    
    tinyxml2::XMLDocument* doc;
};

#endif	/* XMLDOCUMENT_H */

