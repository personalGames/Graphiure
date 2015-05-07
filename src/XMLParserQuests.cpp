/* 
 * File:   XMLParserQuests.cpp
 * Author: dorian
 * 
 * Created on 7 de mayo de 2015, 13:48
 */

#include "XMLParserQuests.h"

XMLParserQuests::XMLParserQuests() {
}

XMLParserQuests::~XMLParserQuests() {
}

void XMLParserQuests::parse(DataUnion& data) {
//get first node
    tinyxml2::XMLElement* quest = doc->FirstChildElement("Quest");

    std::vector<Quest*>* result=new std::vector<Quest*>();
    Quest* oneQuest;
    //pilla cada maquina de turing
    while(quest){
        int idQuest=quest->IntAttribute("id");
        sf::String* text=new sf::String(quest->Attribute("text"));
        sf::Time time = sf::seconds(quest->IntAttribute("time"));
        oneQuest=new Quest(idQuest, text, time);
        
        tinyxml2::XMLElement* partQuest=quest->FirstChildElement("part");
        while(partQuest){
            //TypeQuest type, IdEntity destiny, IdEntity origin, Actions action
            int destiny=partQuest->IntAttribute("id");
            int origin=partQuest->IntAttribute("idOrigin");
            sf::String typeString=partQuest->Attribute("type");
            TypeQuest type;
            if(typeString=="talk"){
                type=TypeQuest::TALK;
            }else if(typeString=="action"){
                type=TypeQuest::ACTION;
            }else if(typeString=="kill"){
                type=TypeQuest::KILL;
            }else if(typeString=="carry"){
                type=TypeQuest::CARRY;
            }
            
            PartQuest* part=new PartQuest(type, destiny, origin);
            oneQuest->addPartQuest(part);
            partQuest=partQuest->NextSiblingElement("part");
        }
        result->push_back(oneQuest);
        quest=quest->NextSiblingElement("Quest");
    }
    
    data.quests=result;
}
