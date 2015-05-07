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
    
    inline Actions GetAction() const {
        return action;
    }

    inline void SetAction(Actions action) {
        this->action = action;
    }

    inline IdEntity GetIdDestiny() const {
        return idDestiny;
    }

    inline void SetIdDestiny(IdEntity idDestiny) {
        this->idDestiny = idDestiny;
    }

    inline IdEntity GetIdOrigin() const {
        return idOrigin;
    }

    inline void SetIdOrigin(IdEntity idOrigin) {
        this->idOrigin = idOrigin;
    }

    inline TypeQuest GetType() const {
        return type;
    }

    inline void SetType(TypeQuest type) {
        this->type = type;
    }

    inline bool IsDone() const {
        return done;
    }

    inline void SetDone(bool done) {
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

