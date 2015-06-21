/* 
 * File:   Talk.h
 * Author: dorian
 *
 * Created on 26 de abril de 2015, 11:22
 */

#ifndef TALK_H
#define	TALK_H

#include <SFML/System/String.hpp>

/**
 * Estructura para guardar una conversación
 */
struct Talk {
    /**
     * Constructor
     * @param phrase frase a decir
     */
    Talk(sf::String* phrase){
        this->phrase=phrase;
    }
    sf::String* phrase;

};

#endif	/* TALK_H */

