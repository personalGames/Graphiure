/* 
 * File:   Utilities.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 17:53
 */

#ifndef UTILITIES_H
#define	UTILITIES_H

#include <SFML/Graphics.hpp>
//#include "Animation.h"
#include <sstream>
#include <vector>
#include <string.h>
#include <cmath>
#include <cassert>

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

// Convert enumerators to strings
//std::string toString(sf::Keyboard::Key key);


// Call setOrigin() with the center of the object
void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
//void centerOrigin(Animation& animation);

// Degree/radian conversion
float toDegree(float radian);
float toRadian(float degree);

// Random number generation
int randomInt(int exclusiveMax);

// Vector operations
float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);

template <typename T>
std::string toString(const T& value) {
    std::stringstream stream;
    stream << value;
    return stream.str();
}

/**
 * Needs to ALWAYS free the vector when used
 * @param convert
 * @return 
 */
std::vector<char>* convertString(std::string convert);

template <class E>
void deleteVector(std::vector<E> &deleted){
    deleted.clear();
    std::vector<E>(deleted).swap(deleted);
}

std::vector<std::string> &split(const std::string &s, 
                                char delim, std::vector<std::string> &elems);


std::vector<std::string> split(const std::string &s, char delim);

#endif	/* UTILITIES_H */

