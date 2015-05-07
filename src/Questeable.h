/* 
 * File:   Questeable.h
 * Author: dorian
 *
 * Created on 7 de mayo de 2015, 12:54
 */

#ifndef QUESTEABLE_H
#define	QUESTEABLE_H

#include "PartQuest.h"


class Questeable {
public:
    Questeable(int id, PartQuest* quest);
    Questeable(const Questeable& orig);
    virtual ~Questeable();
    
    bool isDone();
    
    inline int getIdQuest() const {
        return idQuest;
    }

    void setDone(bool done);
    
private:
    PartQuest* quest;
    int idQuest;

};

#endif	/* QUESTEABLE_H */

