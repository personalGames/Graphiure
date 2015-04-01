/* 
 * File:   XMLParserCollisions.cpp
 * Author: dorian
 * 
 * Created on 1 de abril de 2015, 14:01
 */

#include "XMLParserCollisions.h"

XMLParserCollisions::XMLParserCollisions() {

}

XMLParserCollisions::~XMLParserCollisions() {

}

void XMLParserCollisions::parse(DataUnion& data) {
    std::vector<StructCollision*>* result = new std::vector<StructCollision*>();

    //get the node of collisions
    tinyxml2::XMLElement* collisions = doc->FirstChildElement("Collision");
    //get the object/collision 
    tinyxml2::XMLElement* object = collisions->FirstChildElement("object");
    while (object) {
        //creo el objeto colisionable a crear
        StructCollision* collisionObject=new StructCollision();
        collisionObject->vertices=new sf::VertexArray();
        
        //get the position
        sf::Vector2f position(object->DoubleAttribute("x"), object->DoubleAttribute("y"));
        collisionObject->position=position;
        collisionObject->typeCollision=object->Attribute("type");
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
                collisionObject->vertices->append(vertex);
                vertex=sf::Vertex();
            }
            isX=!isX;
            number = strtok(nullptr, " ,");
        }
        result->push_back(collisionObject);
        object = object->NextSiblingElement("object");
    }

    data.collisions = result;
}
