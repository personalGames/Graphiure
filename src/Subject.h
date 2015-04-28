/* 
 * File:   Subject.h
 * Author: dorian
 *
 * Created on 27 de abril de 2015, 11:50
 */

#ifndef SUBJECT_H
#define	SUBJECT_H

#include <vector>
#include "Message.h"

class Subject {
private:
    // 1. "independent" functionality
    std::vector<class Observer*> views;
    Message value; //el mensaje
public:

    Subject() : value() {
    }
    
    inline void attach(Observer *obs) {
        views.push_back(obs);
    }

    inline void detach(Observer *obs);

    void setMessage(Message& val) {
        value = val;
        notify();
    }

    Message getMessage() {
        return value;
    }

    void notify();

};

#endif	/* SUBJECT_H */

