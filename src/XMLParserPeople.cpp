/* 
 * File:   XMLParserPeople.cpp
 * Author: dorian
 * 
 * Created on 20 de junio de 2015, 21:51
 */

#include "XMLParserPeople.h"

XMLParserPeople::XMLParserPeople() {
}

XMLParserPeople::~XMLParserPeople() {
}

void XMLParserPeople::parse(DataUnion& data, std::string id) {
    
}


void XMLParserPeople::parse(DataUnion& data) {
    StructPeople* result = new StructPeople();
    
    tinyxml2::XMLElement* people= doc->FirstChildElement("people");
    tinyxml2::XMLElement* character=people->FirstChildElement("character");
    if (character== nullptr) {
        std::cout << "Vacio" << std::endl;
    }
    
    std::string* nameCharacter=new std::string(character->Attribute("id"));
    result->character=nameCharacter;
    
    //for every layer map...
    tinyxml2::XMLElement* layer = people->FirstChildElement("villager");
    if (layer== nullptr) {
        std::cout << "Vacio" << std::endl;
    }
    while (layer) {
        nameCharacter=new std::string(layer->Attribute("id"));
        result->villagers->push_back(nameCharacter);
        
        layer = layer->NextSiblingElement("villager");
    }
    
    data.people=result;
}
