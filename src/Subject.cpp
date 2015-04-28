/* 
 * File:   Subject.cpp
 * Author: dorian
 * 
 * Created on 27 de abril de 2015, 11:50
 */

#include "Subject.h"
#include "Observer.h"

void Subject::notify() {
    for (unsigned int i = 0; i < views.size(); i++) {
        views[i]->update();
    }
}

void Subject::detach(Observer* obs) {
    for (std::vector<Observer*>::iterator it = views.begin(); it != views.end();) {
        if ((*it)->getId() == obs->getId()) {
            views.erase(it);
        } else {
            ++it;
        }
    }
}
