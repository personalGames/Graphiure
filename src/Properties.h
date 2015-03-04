/* 
 * File:   Properties.h
 * Author: dorian
 *
 * Created on 3 de marzo de 2015, 9:34
 */

#ifndef PROPERTIES_H
#define	PROPERTIES_H

enum class TypeProperty {
    POSITION, //sf::Vector2f
    VELOCITY, //sf::Vector2f
    DRAWABLE,
    WALKABLE, //sf::Drawable
};

struct Animation{
    int x,y;
    Position(int x, int y):x(x),y(y){};
};

#endif	/* PROPERTIES_H */

