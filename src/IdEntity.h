/* 
 * File:   IdEntity.h
 * Author: dorian
 *
 * Created on 19 de marzo de 2015, 11:41
 */

#ifndef IDENTITY_H
#define	IDENTITY_H

#include <functional>

static int count = 0;

class IdEntity {
public:

    IdEntity(int id) : id(id) {
    };

    IdEntity() : id(count) {
        count++;
    };

    IdEntity(const IdEntity& orig) {
        this->id = orig.id;
    };

    virtual ~IdEntity() {
    };

//    std::size_t operator()(const IdEntity &c) const {
//        return std::hash<int>()(c.id);
//    }

    inline bool operator==(const IdEntity lhs) {
        return lhs.id == this->id;
    }

    inline bool operator!=(const IdEntity& lhs) {
        return !operator==(lhs);
    }

    inline bool operator<(const IdEntity& lhs) {
        return lhs.id<this->id;
    }

    inline bool operator>(const IdEntity& lhs) {
        return operator<(lhs);
    }

    inline bool operator<=(const IdEntity& lhs) {
        return !operator>(lhs);
    }

    inline bool operator>=(const IdEntity& lhs) {
        return !operator<(lhs);
    }

    inline int getId() const {
        return id;
    }





private:
    int id;
};

#endif	/* IDENTITY_H */

