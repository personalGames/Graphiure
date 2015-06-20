/* 
 * File:   Entity2.cpp
 * Author: dorian
 * 
 * Created on 3 de marzo de 2015, 9:30
 */

#include "Entity.h"

Entity::Entity(): Entity(Category::NONE) {

}

Entity::Entity(Category category):id(), destroyed(false), category(category), idXml(-1) {

}


Entity::~Entity() {

}
