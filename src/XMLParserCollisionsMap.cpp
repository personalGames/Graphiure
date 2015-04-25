/* 
 * File:   XMLParserCollisionsMap.cpp
 * Author: dorian
 * 
 * Created on 19 de marzo de 2015, 12:36
 */

#include "XMLParserCollisionsMap.h"

#include "Utilities.h"
#include "ConvexTest.h"
#include <iostream>
#include <cassert>

XMLParserCollisionsMap::XMLParserCollisionsMap() {
}

XMLParserCollisionsMap::~XMLParserCollisionsMap() {
}

void XMLParserCollisionsMap::parse(DataUnion& data) {
    std::vector<StructCollision*>* result = new std::vector<StructCollision*>();

    //get root node
    tinyxml2::XMLElement* detailsMap = doc->FirstChildElement("map");
    if (detailsMap == nullptr) {
        std::cout << "Vacio" << std::endl;
    }

    //get the node of collisions
    tinyxml2::XMLElement* collisions = detailsMap->FirstChildElement("objectgroup");
    //get the object/collision 
    tinyxml2::XMLElement* object = collisions->FirstChildElement("object");
    while (object) {
        //creo el objeto colisionable a crear
        StructCollision* collisionObject = new StructCollision();
        collisionObject->vertices = new sf::VertexArray();

        //get the position
        sf::Vector2f position(object->DoubleAttribute("x"), object->DoubleAttribute("y"));
        collisionObject->position = position;
        collisionObject->typeCollision = object->Attribute("type");
        //get the points
        tinyxml2::XMLElement* vertices = object->FirstChildElement("polyline");

        //recojo los puntos
        char* points = strdup(vertices->Attribute("points"));
        //trato la tira de puntos
        char* number = strtok(points, " ,");
        sf::Vertex vertex;
        vertex.color = sf::Color::Red;
        bool isX = true;
        while (number != nullptr) {
            if (isX) {
                vertex = sf::Vertex();
                vertex.position.x = atof(number);
            } else {
                vertex.position.y = atof(number);
                collisionObject->vertices->append(vertex);
                
            }
            isX = !isX;
            number = strtok(nullptr, " ,");
        }

        //compruebo que el poligono esté bien formado
        //assert(polygonIsConvex(collisionObject));
        if (!polygonIsConvex(collisionObject)) {
            std::cout << "No es convexo" << std::endl;
        }
        result->push_back(collisionObject);
        object = object->NextSiblingElement("object");
    }

    data.collisions = result;
}

