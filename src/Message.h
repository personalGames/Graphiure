/* 
 * File:   Message.h
 * Author: dorian
 *
 * Created on 27 de abril de 2015, 11:49
 */

#ifndef MESSAGE_H
#define	MESSAGE_H

#include "GameStates.h"
#include "IdEntity.h"


class Message {
public:
    Message(){};
    Message(GameStates state):state(state){};
    virtual ~Message();
    
    inline GameStates getState() const {
        return state;
    }

    inline void setState(GameStates state) {
        this->state = state;
    }

    IdEntity getIdEntity() const {
        return idEntity;
    }
    
    void setIdEntity(IdEntity id){
        this->idEntity=id;
    }

    
private:
    GameStates state;
    IdEntity idEntity;
};

#endif	/* MESSAGE_H */

