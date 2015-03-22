/* 
 * File:   EnumHash.h
 * Author: dorian
 *
 * Created on 28 de noviembre de 2014, 17:52
 */

#ifndef ENUMHASH_H
#define	ENUMHASH_H

struct HashEnum {
    template <typename T>
    std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};

#endif	/* ENUMHASH_H */

