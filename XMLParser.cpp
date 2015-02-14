/* 
 * File:   XMLParser.cpp
 * Author: dorian
 * 
 * Created on 12 de febrero de 2015, 16:11
 */

#include "XMLParser.h"
#include <iostream>
using namespace tinyxml2;

XMLParser::XMLParser(std::string path) {
    std::vector<char> writable = *convertString(path);

    doc.LoadFile(&writable[0]);
    if (doc.ErrorID() != 0) {
        std::cout << "Error: " << doc.ErrorID() << " - " << doc.ErrorName() << std::endl;
    }

    //delete the created vector
    deleteVector(writable);
}

XMLParser::XMLParser(const XMLParser& orig) {
}

XMLParser::~XMLParser() {
}

StructMap* XMLParser::readMap() {
    StructMap* result = new StructMap();
    //get root node
    XMLElement* detailsMap = doc.FirstChildElement("map");
    if (detailsMap == nullptr) {
        std::cout << "Vacio" << std::endl;
    }

    uint width;
    uint height;
    width=detailsMap->IntAttribute("width");
    height=detailsMap->IntAttribute("height");
    
    result->numberColumns = width;
    result->numberRows = height;
    
    result->tileWidth=detailsMap->IntAttribute("tilewidth"); 
    result->tileHeight=detailsMap->IntAttribute("tileheight");
    
    //for every layer map...
    //TODO
    XMLElement* detailsLayer = detailsMap->FirstChildElement("tileset")->FirstChildElement("layer");
    //result->layer=detailsLayer->Attribute("name");
    // populate the vertex array, with one quad per tile
    result->tiles = new int[width * height];
    uint i=0; 
    XMLElement* child=detailsLayer->FirstChildElement();
    
    while(child){
        std::string dataRow(child->GetText());
        std::vector<std::string> numbers = std::move(split(dataRow, ','));
        for (uint j = 0; j < numbers.size(); ++j) {
              result->tiles[i + j * width]= atoi(numbers[j].c_str());
        }
        
        i++;
        child=child->NextSiblingElement();
    }

    return result;
}

