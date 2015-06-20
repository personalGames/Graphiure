/* 
 * File:   Quest.cpp
 * Author: dorian
 * 
 * Created on 7 de mayo de 2015, 11:36
 */

#include "Quest.h"
#include <iostream>

Quest::Quest(int id, sf::String* text) : Quest(id, text, sf::Time(sf::seconds(0))) {
}

Quest::Quest(int id, sf::String* text, sf::Time time) : opened(false) {
    this->id = id;
    this->textQuest = text;
    this->time = time;
    this->timer = sf::Time::Zero;
}

void Quest::addPartQuest(PartQuest* part) {
    list.push_back(part);
}

bool Quest::isFinished() {
    return list.empty();
}

std::vector<int> Quest::onFinished() {
    return idQuestToOpen;
}

void Quest::removeQuestOpen(int id) {
    std::remove_if(idQuestToOpen.begin(), idQuestToOpen.end(), [id](int i) {
        return id == i;
    });
}

void Quest::update(sf::Time dt) {
    bool finish = false;
    for (std::vector<PartQuest*>::iterator iter = list.begin(); iter != list.end(); ++iter) {
        if ((*iter)->isDone()) {
            if (isInOrder() && finish) {
                (*iter)->setDone(false);
            } else {
                doneList.push_back(*iter);
                iter = list.erase(iter);
                --iter;
            }
        } else {
            finish = true;
        }
    }

    if (time != sf::Time::Zero) {
        timer += dt;
        if (timer > time) {
            for (std::vector<PartQuest*>::reverse_iterator iter = doneList.rbegin(); iter != doneList.rend(); ++iter) {
                (*iter)->setDone(false);
                list.insert(list.begin(), *iter);
                ++iter;
            }
        }
    }
}

Quest::Quest(const Quest& orig) {
}

Quest::~Quest() {
}

