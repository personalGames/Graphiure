/* 
 * File:   StructPeople.h
 * Author: dorian
 *
 * Created on 20 de junio de 2015, 21:52
 */

#ifndef STRUCTPEOPLE_H
#define	STRUCTPEOPLE_H

#include <vector>
#include <string>


struct StructPeople{

    StructPeople();
    virtual ~StructPeople();
    
    std::vector<std::string*>* villagers;
    std::string* character;
};

#endif	/* STRUCTPEOPLE_H */

