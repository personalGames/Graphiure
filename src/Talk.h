/* 
 * File:   Talk.h
 * Author: dorian
 *
 * Created on 26 de abril de 2015, 11:22
 */

#ifndef TALK_H
#define	TALK_H

#include <string>

struct Talk {
    Talk(std::string* phrase){
        this->phrase=phrase;
    }
    std::string* phrase;

};

#endif	/* TALK_H */

