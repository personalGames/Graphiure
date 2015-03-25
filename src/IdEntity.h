/* 
 * File:   IdEntity.h
 * Author: dorian
 *
 * Created on 19 de marzo de 2015, 11:41
 */

#ifndef IDENTITY_H
#define	IDENTITY_H

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
    

    inline bool operator==(const IdEntity lhs) const{
        return lhs.id == id;
    }

    inline bool operator!=(const IdEntity& lhs) const {
        return !operator==(lhs);
    }

    inline bool operator<(const IdEntity& lhs) const {
        return lhs.id<id;
    }

    inline bool operator>(const IdEntity& lhs) const {
        return operator<(lhs);
    }

    inline bool operator<=(const IdEntity& lhs) const {
        return !operator>(lhs);
    }

    inline bool operator>=(const IdEntity& lhs) const {
        return !operator<(lhs);
    }

    inline int getId() const {
        return id;
    }





private:
    int id;
};

#endif	/* IDENTITY_H */

