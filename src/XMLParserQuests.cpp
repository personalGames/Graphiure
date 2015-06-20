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
    //pilla cada quest
    while(quest){
        int idQuest=quest->IntAttribute("id");
        sf::String* text=new sf::String(quest->Attribute("text"));
        int seconds=quest->IntAttribute("time");
        sf::Time time;
        if(seconds==0){
            time=sf::Time::Zero;
        }else{
            time=sf::seconds(seconds);
        }
        oneQuest=new Quest(idQuest, text, time);
        
        bool order=quest->BoolAttribute("order");
        oneQuest->setInOrder(order);
        std::string finish=std::string(quest->Attribute("finish"));
        std::vector<std::string> resultFinish=split(finish, ',');
        for(std::vector<std::string>::iterator it=resultFinish.begin(); it!=resultFinish.end(); ++it){
            oneQuest->addQuestOpen(atoi((*it).c_str()));
        }
        
        tinyxml2::XMLElement* partQuest=quest->FirstChildElement("part");
        while(partQuest){
            //TypeQuest type, IdEntity destiny, IdEntity origin, Actions action
//            int id=partQuest->IntAttribute("id");
            int destiny=partQuest->IntAttribute("entity");
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
