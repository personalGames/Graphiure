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
#include "../include/tinyxml2.h"
#include "DataUnion.h"
#include <vector>
#include <iostream>
#include "ResourceHolder.h"
#include "XMLDocument.h"

/**
 * Clase base para un parseador de xml
 */
class IXMLParser {
public:
    /**
     * Devuelve el parseador concreto al tipo escogido
     * @param choice tipo de parseador requerido
     * @return parseador pedido
     */
    static IXMLParser *make_parser(TypeParser choice);
    virtual ~IXMLParser();

    /**
     * Setea el xml que parseará
     * @param path documento xml a parsear
     */
    void setXML(tinyxml2::XMLDocument& path);
    /**
     * Setea el xml que parseará
     * @param path documento a parsear
     */
    void setXML(XMLDocument& path);
    /**
     * Setea los recursos de imágenes que puede necesitar el parseador
     * @param textures imagenes
     */
    void setResources(ResourceHolder<std::string, sf::Texture>* textures);
    /**
     * Parsea los datos
     * @param data
     */
    virtual void parse(DataUnion& data)=0;
    
protected:
    /**
     * Documento a parsear
     */
    tinyxml2::XMLDocument* doc;
    /**
     * Imágenes a usar
     */
    ResourceHolder<std::string, sf::Texture>* textures;
};

#endif	/* IXMLPARSER_H */

