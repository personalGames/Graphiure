/* 
 * File:   XMLParserCollisionsMap.cpp
 * Author: dorian
 * 
 * Created on 19 de marzo de 2015, 12:36
 */

#include "XMLParserCollisionsMap.h"

XMLParserCollisionsMap::XMLParserCollisionsMap() {
}

XMLParserCollisionsMap::~XMLParserCollisionsMap() {
}

void XMLParserCollisionsMap::parse(DataUnion& data, std::string id) {

}

void XMLParserCollisionsMap::parse(DataUnion& data) {
    std::vector<Collision*>* result = new std::vector<Collision*>();

    //get root node
    tinyxml2::XMLElement* detailsMap = doc.FirstChildElement("map");
    if (detailsMap == nullptr) {
        std::cout << "Vacio" << std::endl;
    }

    //get the node of collisions
    tinyxml2::XMLElement* collisions = detailsMap->FirstChildElement("objectgroup");
    //get the object/collision 
    tinyxml2::XMLElement* object = collisions->FirstChildElement("object");
    while (object) {
        //creo el objeto colisionable a crear
        Collision* collisionObject = new Collision();
        
        //get the position
        sf::Transformable* transform=new sf::Transformable();
        transform->setPosition(object->DoubleAttribute("x"), object->DoubleAttribute("y"));
        collisionObject->update(*transform);
        
        //get the points
        tinyxml2::XMLElement* vertices = object->FirstChildElement("polyline");
        
        //recojo los puntos
        char* points = strdup(vertices->Attribute("points"));
        //trato la tira de puntos
        char* number = strtok(points, " ,");
        sf::Vertex vertex=sf::Vertex();
        bool isX=true;
        while (number != nullptr) {
            if(isX){
                vertex.position.x=atof(number);
            }else{
                vertex.position.y=atof(number);
                collisionObject->addVertice(vertex);
                vertex=sf::Vertex();
            }
            isX=!isX;
            number = strtok(nullptr, " ,");
        }
        result->push_back(collisionObject);
        object = object->NextSiblingElement();
    }

    data.collisions = result;
}
