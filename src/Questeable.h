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
    Questeable(int id);
    Questeable(const Questeable& orig);
    virtual ~Questeable();
    
    void addPartQuest(PartQuest* quest);
//    bool isDone();
    
    inline int getIdQuest() const {
        return idQuest;
    }
    
    inline const std::vector<PartQuest*>& getPartQuest(){
        return quest;
    }

//    void setDone(bool done);
    
private:
    std::vector<PartQuest*> quest;
    int idQuest;

};

#endif	/* QUESTEABLE_H */

