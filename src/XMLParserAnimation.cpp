/* 
 * File:   XMLParserAnimation.cpp
 * Author: dorian
 * 
 * Created on 11 de marzo de 2015, 11:08
 */

#include "XMLParserAnimation.h"
#include "ResourceHolder.h"
#include "Context.h"
#include "StructAnimation.h"
#include <iostream>

XMLParserAnimation::XMLParserAnimation() {
}

XMLParserAnimation::~XMLParserAnimation() {
}


void XMLParserAnimation::parse(DataUnion& data) {
    StructAnimation* result=new StructAnimation();
    //get first node
    tinyxml2::XMLElement* animation = doc->FirstChildElement("Animation");;

    
    //pilla las animaciones, cada animación se guarda en la lista
    //por ahora considero que todos son del mismo entity (debug)
    while(animation){
        tinyxml2::XMLElement* anim=animation->FirstChildElement("frame");
        std::string image(animation->Attribute("idImage"));
        bool replay=animation->BoolAttribute("replay");
        bool wait=animation->BoolAttribute("wait");
        storeFrames(image, anim, result, replay, wait);
        
       animation=animation->NextSiblingElement("Animation");
    }
    data.animations=result;
}

//pilla los frames, con los vértices de cada frame
void XMLParserAnimation::storeFrames(std::string image, tinyxml2::XMLElement* node, StructAnimation* animation, bool replay, bool wait){
    if(node!=nullptr && strcmp(node->Name(),"frame")!=0){
        return;
    }
    tinyxml2::XMLElement* vertice;
    Animation* anim=new Animation();
    
    //image for this animation
    textures->load(image, "Media/Textures/"+image);
    textures->get(image);
    anim->setSpriteSheet(textures->get(image));
    anim->setWait(wait);
    anim->setReplay(replay);
    //recojo los frames de una animación concreta
    while(node){
        sf::IntRect rect;
        int i=0;
        //recojo los vértices
        vertice=node->FirstChildElement("vertice");
        
        while(vertice){
            int value=vertice->IntAttribute("value");
            switch(i){
                case 0:
                    rect.left=value;
                    break;
                case 1:
                    rect.top=value;
                    break;
                case 2:
                    rect.width=value;
                    break;
                case 3:
                    rect.height=value;
                    break;
            }
            i++;
            vertice=vertice->NextSiblingElement("vertice");
        }
        //añado el frame
        anim->addFrame(rect);
        
        node=node->NextSiblingElement("frame");
    }
    //ya tengo una animación con sus frames, lo añado a la lista de animaciones
    animation->animations->push_back(anim);
}