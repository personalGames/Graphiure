/* 
 * File:   XMLParserStateMachines.cpp
 * Author: dorian
 * 
 * Created on 13 de marzo de 2015, 10:35
 */

#include "XMLParserStateMachines.h"
#include "StateMachine.h"
#include "DataUnion.h"

XMLParserStateMachines::XMLParserStateMachines() {

}

XMLParserStateMachines::~XMLParserStateMachines() {

}

DataUnion XMLParserStateMachines::parse(std::string id) {
    DataUnion data;
    return data;
}

DataUnion XMLParserStateMachines::parse() {
    //get first node
    tinyxml2::XMLElement* stateMachine = doc.FirstChildElement("StateMachine");
    StateMachine* result;
    //pilla cada maquina de turing
    while(stateMachine){
        int numberStates=stateMachine->IntAttribute("numberStates");
        result=new StateMachine(numberStates);
        
        //por cada transición...
        tinyxml2::XMLElement* transicion=stateMachine->FirstChildElement("Transition");
        while(transicion){
            int state=transicion->IntAttribute("state");
            int entry=transicion->IntAttribute("entry");
            int newState=transicion->IntAttribute("newState");
            Transition tran=Transition(state,entry,newState);
            result->addTransition(tran);
            
            transicion=transicion->NextSiblingElement();
        }
        
       stateMachine=stateMachine->NextSiblingElement();
    }
    
    DataUnion data=DataUnion();
    data.stateMachine=result;
    return data;
}
