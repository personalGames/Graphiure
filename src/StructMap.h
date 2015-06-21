/* 
 * File:   StructMap.h
 * Author: dorian
 *
 * Created on 12 de febrero de 2015, 17:40
 */

#ifndef STRUCTMAP_H
#define	STRUCTMAP_H

#include <vector>
#include "Layer.h"
#include <SFML/Graphics.hpp>

/**
 * Estructura para guardar información de tiles de un mapa
 */
struct StructMap{

    StructMap();
    virtual ~StructMap();
    
    
    int numberColumns;
    int numberRows;
    int tileHeight;
    int tileWidth;
    int* tiles; //whole background
    std::vector< sf::Vector3i >* underground; //another layer not totally fully
};

#endif	/* STRUCTMAP_H */

