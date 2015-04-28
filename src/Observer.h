/* 
 * File:   Observer.h
 * Author: dorian
 *
 * Created on 27 de abril de 2015, 11:49
 */

#ifndef OBSERVER_H
#define	OBSERVER_H

#include "Subject.h"

static int countObserver = 0;

class Observer {
    
private:
    // 2. "dependent" functionality
    Subject *model;
    int id;
    
public:
    
    inline int getId(){
        return id;
    }

    Observer(): id(countObserver){
        countObserver++;
    }
    void setSubject(Subject* mod);
    virtual void update() = 0;
    
protected:

    inline Subject *getSubject() {
        return model;
    }

};

#endif	/* OBSERVER_H */

