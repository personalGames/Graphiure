/* 
 * File:   HashIdEntity.h
 * Author: dorian
 *
 * Created on 22 de marzo de 2015, 20:44
 */

#ifndef HASHIDENTITY_H
#define	HASHIDENTITY_H

#include "IdEntity.h"
#include <functional>

/**
 * Clase para el hasheo de IdEntity
 * @param t idEntity a calcular
 * @return hash calculado
 */
class HashIdEntity {
public:
    const std::size_t operator()(IdEntity const &t) const {
        std::hash<int> hashId;
        std::size_t result=hashId(t.getId());
        return result;
    }
};

#endif	/* HASHIDENTITY_H */

