/* 
 * File:   PartQuest.h
 * Author: dorian
 *
 * Created on 7 de mayo de 2015, 11:26
 */

#ifndef PARTQUEST_H
#define	PARTQUEST_H

#include "TypeQuest.h"
#include "IdEntity.h"
#include "Actions.h"


class PartQuest {
public:
    PartQuest(TypeQuest type, IdEntity destiny, IdEntity origin);
    PartQuest(TypeQuest type, IdEntity destiny, IdEntity origin, Actions action);
    PartQuest(const PartQuest& orig);
    virtual ~PartQuest();
    
    inline Actions getAction() const {
        return action;
    }

    inline void setAction(Actions action) {
        this->action = action;
    }

    inline IdEntity getIdDestiny() const {
        return idDestiny;
    }

    inline void setIdDestiny(IdEntity idDestiny) {
        this->idDestiny = idDestiny;
    }

    inline IdEntity getIdOrigin() const {
        return idOrigin;
    }

    inline void setIdOrigin(IdEntity idOrigin) {
        this->idOrigin = idOrigin;
    }

    inline TypeQuest getType() const {
        return type;
    }

    inline void setType(TypeQuest type) {
        this->type = type;
    }

    inline bool isDone() const {
        return done;
    }

    inline void setDone(bool done) {
        this->done = done;
    }
    
private:
    TypeQuest type;
    IdEntity idDestiny;
    IdEntity idOrigin;
    Actions action;
    bool done;
    
    
};

#endif	/* PARTQUEST_H */

