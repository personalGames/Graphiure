/* 
 * File:   FactoryGameObjects.h
 * Author: dorian
 *
 * Created on 30 de marzo de 2015, 21:06
 */

#include "FactoryGameObjects.h"
#include "Character.h"
#include <iostream>

std::unique_ptr<GameObjects> FactoryGameObjects::getFactory(std::string type){
    if(type.compare("Block")==0){
        return std::unique_ptr<StaticBlock>(new StaticBlock());
    }else if(type.compare("Hole")==0){
        return std::unique_ptr<Hole>(new Hole());
    }else if(type.compare("Character")==0){
        return std::unique_ptr<Character>(new Character());
    }else{
        return std::unique_ptr<StaticBlock>(new StaticBlock());
    }
}