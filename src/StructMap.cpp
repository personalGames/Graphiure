/* 
 * File:   StructMap.h
 * Author: dorian
 *
 * Created on 12 de febrero de 2015, 17:40
 */

#include "StructMap.h"

StructMap::StructMap(): numberColumns(0), numberRows(0), tileHeight(0),
        tileWidth(0), tiles(), underground() {
    underground=new std::vector< sf::Vector3i >();
    villagers=new std::vector<std::string*>();
}

StructMap::~StructMap() {
    delete tiles;
    delete underground; //delete content vector!!
}
