/* 
 * File:   StructMap.h
 * Author: dorian
 *
 * Created on 12 de febrero de 2015, 17:40
 */

#ifndef STRUCTMAP_H
#define	STRUCTMAP_H

#include <vector>
#include "Layer.h"


class StructMap{
public:
    StructMap();
    virtual ~StructMap();
    
    int numberColumns;
    int numberRows;
    int tileHeight;
    int tileWidth;
    int* tiles;
};

#endif	/* STRUCTMAP_H */

