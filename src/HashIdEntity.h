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

class HashIdEntity {
public:
//    template <IdEntity>
    const std::size_t operator()(IdEntity const &t) const {
        return static_cast<std::size_t>(t.getId());
    }
};

#endif	/* HASHIDENTITY_H */

