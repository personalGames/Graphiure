/* 
 * File:   QuadTree.cpp
 * Author: dorian
 * 
 * Created on 15 de marzo de 2015, 18:20
 */

#include "QuadTree.h"

QuadTree::QuadTree(int level, sf::Rect<int> bounds) : level(level), objects(), bounds(bounds), nodes(4) {

};

void QuadTree::clear() {
//    for(std::list<Entity*>::iterator it = objects.begin(); it != objects.end(); ++it) {
//        delete *(it);
//    }
    objects.clear();

    for (uint i = 0; i < nodes.size(); ++i) {
        if (nodes[i] != nullptr) {
            nodes[i]->clear();
            delete nodes[i];
        }
    }
    nodes.clear();
}

int QuadTree::getIndex(Collision collision) {
    sf::Rect<int> bound=collision.getAABB();
    int index = -1;
    double verticalMidpoint = bounds.left + (bounds.width / 2);
    double horizontalMidpoint = bounds.top + (bounds.height / 2);

    // Object can completely fit within the top quadrants
    bool topQuadrant = (bound.top < horizontalMidpoint && bound.top + bound.height < horizontalMidpoint);
    // Object can completely fit within the bottom quadrants
    bool bottomQuadrant = (bound.top > horizontalMidpoint);

    // Object can completely fit within the left quadrants
    if (bound.left < verticalMidpoint && bound.left + bound.width < verticalMidpoint) {
        if (topQuadrant) {
            index = 1;
        } else if (bottomQuadrant) {
            index = 2;
        }
    }
    // Object can completely fit within the right quadrants
    else if (bound.left > verticalMidpoint) {
        if (topQuadrant) {
            index = 0;
        } else if (bottomQuadrant) {
            index = 3;
        }
    }

    return index;
}

void QuadTree::insert(Entity* objectNew) {
    if (nodes[0] != nullptr) {
        int index = getIndex(objectNew->Get<Collision>("Collision"));

        if (index != -1) {
            nodes[index]->insert(objectNew);

            return;
        }
    }

    objects.push_back(objectNew);

    if (objects.size() > MAX_OCCUPANTS && level < MAX_LEVELS) {
        if (nodes[0] == nullptr) {
            split();
        }

        for(std::list<Entity*>::iterator it = objects.begin(); it != objects.end(); ++it) {
            Entity* ob=*(it);
            int index = getIndex(ob->Get<Collision>("Collision"));
            if (index != -1) {
                nodes[index]->insert(ob);
                it=objects.erase(it);
            } 
        }
    }
}

void QuadTree::split() {
    int subWidth = static_cast<int> (bounds.width / 2);
    int subHeight = static_cast<int> (bounds.height / 2);
    int x = bounds.left;
    int y = bounds.top;

    nodes[0] = new QuadTree(level + 1, sf::Rect<int>(x + subWidth, y, subWidth, subHeight));
    nodes[1] = new QuadTree(level + 1, sf::Rect<int>(x, y, subWidth, subHeight));
    nodes[2] = new QuadTree(level + 1, sf::Rect<int>(x, y + subHeight, subWidth, subHeight));
    nodes[3] = new QuadTree(level + 1, sf::Rect<int>(x + subWidth, y + subHeight, subWidth, subHeight));
}

std::vector<Entity*>* QuadTree::retrieve(std::vector<Entity*>* list, Entity* object) {
    int index = getIndex(object->Get<Collision>("Collision"));
    if (index != -1 && nodes[0] != nullptr) {
        nodes[index]->retrieve(list, object);
    }
    
    for(std::list<Entity*>::iterator it = objects.begin(); it != objects.end(); ++it) {
            list->push_back(*it);
    }

    return list;
}

//void QuadTree::toString() {
//    
//    for(std::list<Entity*>::iterator it = objects.begin(); it != objects.end(); ++it) {
//        int le=level;
//        while(le>0){
//            std::cout<<"  ";
//            --le;
//        }
//        std::cout<<"XY: "<<(*(it))->bounds.left<<" "<<(*(it))->bounds.top<<". Size: "<<(*(it))->bounds.width<<" "<<(*(it))->bounds.height<<std::endl;
//    }
//    for(uint i=0; i<nodes.size(); ++i){
//        if(nodes[i]!=nullptr){
//            nodes[i]->toString();
//        }
//    }
//}
