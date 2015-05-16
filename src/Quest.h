/* 
 * File:   Quest.h
 * Author: dorian
 *
 * Created on 7 de mayo de 2015, 11:36
 */

#ifndef QUEST_H
#define	QUEST_H

#include "PartQuest.h"
#include <SFML/System/Time.hpp>
#include <vector>
#include <algorithm>
#include <SFML/System/String.hpp>


class Quest {
public:
    Quest(int id, sf::String* text);
    Quest(int id, sf::String* text, sf::Time time);
    Quest(const Quest& orig);
    virtual ~Quest();
    
    void addPartQuest(PartQuest* part);
    inline sf::Time getTime() const {
        return time;
    }

    inline void setTime(sf::Time time) {
        this->time = time;
    }
    
    inline sf::String* getText(){
        return textQuest;
    }

    bool isFinished();
    std::vector<int> onFinished();
    void update(sf::Time dt);
    
    inline void addQuestOpen(int id){
        idQuestToOpen.push_back(id);
    }
    
    inline void removeQuestOpen(int id);
    
    int getId() const {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }
    
    bool isOpened() const {
        return opened;
    }

    void setOpened(bool opened) {
        this->opened = opened;
    }
    
    bool isInOrder() const {
        return inOrder;
    }

    void setInOrder(bool inOrder) {
        this->inOrder = inOrder;
    }

    
private:
    int id;
    bool opened;
    std::vector<PartQuest*> list;
    std::vector<PartQuest*> doneList;
    sf::Time time;
    sf::Time timer;
    std::vector<int> idQuestToOpen;
    sf::String* textQuest;
    bool inOrder;
};

#endif	/* QUEST_H */

