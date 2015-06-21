/* 
 * File:   IdEntity.h
 * Author: dorian
 *
 * Created on 19 de marzo de 2015, 11:41
 */

#ifndef IDENTITY_H
#define	IDENTITY_H

static int count = 0;

/**
 * Identificador para una entidad
 */
class IdEntity {
public:
    /**
     * Constructor
     * @param id el id de la entidad
     */
    IdEntity(int id) : id(id) {
    };

    /**
     * Constructor por defecto, se asigna un nuevo identificador no usado
     * hasta el momento
     */
    IdEntity() : id(count) {
        count++;
    };

    /**
     * Constructor copia
     * @param orig otro identificador
     */
    IdEntity(const IdEntity& orig) {
        this->id = orig.id;
    };

    /**
     * Destructor
     */
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

