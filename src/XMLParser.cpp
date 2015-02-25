/* 
 * File:   XMLParser.cpp
 * Author: dorian
 * 
 * Created on 12 de febrero de 2015, 16:11
 */

#include "XMLParser.h"
#include <iostream>

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
    tinyxml2::XMLElement* detailsMap = doc.FirstChildElement("map");
    if (detailsMap == nullptr) {
        std::cout << "Vacio" << std::endl;
    }

    uint width;
    uint height;
    width = detailsMap->IntAttribute("width");
    height = detailsMap->IntAttribute("height");

    result->numberColumns = width;
    result->numberRows = height;

    result->tileWidth = detailsMap->IntAttribute("tilewidth");
    result->tileHeight = detailsMap->IntAttribute("tileheight");

    //for every layer map...
    tinyxml2::XMLElement* layer = detailsMap->FirstChildElement("layer");
    while (layer) {
        const char* nameLayer = layer->Attribute("name");
        if (strcmp(nameLayer, "Background") == 0) {
            parseBackground(result, layer);
            
        } else if (strcmp(nameLayer, "Underground") == 0) {
            parseUnderground(result, layer);
        }
        layer = layer->NextSiblingElement();
    }


    return result;
}

void XMLParser::parseBackground(StructMap* result, tinyxml2::XMLElement* layer) {
    result->tiles = new int[result->numberColumns * result->numberRows];
    uint i = 0;
            
    //get the data element and next, the gid element
    tinyxml2::XMLElement* child = layer->FirstChildElement()->FirstChildElement();

    while (child) {
        result->tiles[i] = child->IntAttribute("gid");
        i++;
        child = child->NextSiblingElement();
    }
}

void XMLParser::parseUnderground(StructMap* result, tinyxml2::XMLElement* layer) {
    uint i = 0;
    //get the data element and next, the gid element
    tinyxml2::XMLElement* child = layer->FirstChildElement()->FirstChildElement();

    int width=result->numberColumns;
    while (child) {
        uint value = child->IntAttribute("gid");
        if (value != 0) {
            int y=i%width;
            int x=i/width;
            
            sf::Vector3i point = *(new sf::Vector3i(y,x,value));
            result->underground->push_back(std::move(point));
        }
        i++;
        child = child->NextSiblingElement();
    }
}
