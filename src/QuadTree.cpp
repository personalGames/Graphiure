/* 
 * File:   QuadTree.cpp
 * Author: dorian
 * 
 * Created on 15 de marzo de 2015, 18:20
 */

#include "QuadTree.h"
#include "ActionStack.h"
#include "Position.h"
#include "Velocity.h"

QuadTree::QuadTree(int level, sf::IntRect bounds) : level(level), objects(), bounds(0, 0, 0, 0), nodes(4) {
    this->bounds.top = static_cast<float> (bounds.top);
    this->bounds.left = static_cast<float> (bounds.left);
    this->bounds.height = static_cast<float> (bounds.height);
    this->bounds.width = static_cast<float> (bounds.width);
};

QuadTree::QuadTree(int level, sf::FloatRect bounds) : level(level), objects(), bounds(bounds), nodes(4) {


};

QuadTree::QuadTree(int level) : level(level), objects(), bounds(0, 0, 0, 0), nodes(4) {

}

void QuadTree::clear() {
    objects.clear();

    for (uint i = 0; i < nodes.size(); ++i) {
        if (nodes[i] != nullptr) {
            nodes[i]->clear();
            delete nodes[i];
        }
    }
    nodes.clear();
}

bool QuadTree::remove(Entity* object) {
    bool result = false;
    int index = getIndex(object->Get<Collision*>("Collision"));
    bool searchMyself = false;
    if (index == -1) {
        searchMyself = true;
    } else {
        if (nodes[index] != nullptr) {
            result = nodes[index]->remove(object);
        } else {
            searchMyself = true;
        }
    }

    if (searchMyself) {
        std::list<Entity*>::iterator it = objects.begin();
        while (it != objects.end() && !result) {
            Entity* ob = *(it);
            if (object->getId() == ob->getId()) {
                objects.erase(it);
                result = true;
            } else {
                ++it;
            }
        }
    }

    return result;
}

int QuadTree::getIndex(Collision* collision) {
    sf::FloatRect bound = collision->getAABBSwept();
    return getIndex(bound);
}

int QuadTree::getIndex(sf::FloatRect rect) {
    sf::FloatRect bound = rect;
    int index = -1;

    //sino esta dentro de mi completamente, directamente no 
    //entrará en los hijos
    if (!inside(rect)) {
        return index;
    }

    double verticalMidpoint = bounds.left + (bounds.width / 2);
    double horizontalMidpoint = bounds.top + (bounds.height / 2);

    // Object can completely fit within the top quadrants
    bool topQuadrant = (bound.top < horizontalMidpoint &&
            bound.top + bound.height < horizontalMidpoint &&
            bound.top > bounds.top);
    // Object can completely fit within the bottom quadrants
    bool bottomQuadrant = (bound.top > horizontalMidpoint &&
            bound.top + bound.height < bounds.top + bounds.height);

    // Object can completely fit within the left quadrants
    if (bound.left < verticalMidpoint && bound.left + bound.width < verticalMidpoint
            && bound.left > bounds.left) {
        if (topQuadrant) {
            index = 1;
        } else if (bottomQuadrant) {
            index = 2;
        }
    }// Object can completely fit within the right quadrants
    else if (bound.left > verticalMidpoint && bound.left + bound.width < bounds.left + bounds.width) {
        if (topQuadrant) {
            index = 0;
        } else if (bottomQuadrant) {
            index = 3;
        }
    }

    return index;
}

QuadTree* QuadTree::getNodeRegion(sf::FloatRect region) {
    int fit = getIndex(region);
    QuadTree* result = nullptr;
    if (fit == -1) {
        result = this;
    } else {
        if (nodes[fit] != nullptr) {
            result = nodes[fit]->getNodeRegion(region);
        } else {
            result = this;
        }
    }
    return result;
}

void QuadTree::insert(Entity* objectNew) {
    Collision* coli = objectNew->Get<Collision*>("Collision");
    sf::FloatRect rect;
    if (objectNew->HasID("Velocity")) {
        rect = coli->getAABBSwept();
    } else {
        rect = coli->getAABB();
    }
    if (nodes[0] != nullptr && !inside(rect)) {
        int index = getIndex(rect);

        if (index != -1) {
            if (nodes[index] != nullptr) {
                nodes[index]->insert(objectNew);
                return;
            }
        }
    }
    objects.push_back(objectNew);

    if (objects.size() > MAX_OCCUPANTS && level < MAX_LEVELS) {
        if (nodes[0] == nullptr) {
            split();
        }
        std::list<Entity*>::iterator it = objects.begin();
        while (it != objects.end()) {
            Entity* ob = *(it);
            int index = getIndex(ob->Get<Collision*>("Collision"));
            if (index != -1) {
                nodes[index]->insert(ob);
                it = objects.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void QuadTree::split() {
    int subWidth = static_cast<int> (bounds.width / 2);
    int subHeight = static_cast<int> (bounds.height / 2);
    int x = bounds.left;
    int y = bounds.top;

    nodes[0] = new QuadTree(level + 1, sf::IntRect(x + subWidth, y, subWidth, subHeight));
    nodes[1] = new QuadTree(level + 1, sf::IntRect(x, y, subWidth, subHeight));
    nodes[2] = new QuadTree(level + 1, sf::IntRect(x, y + subHeight, subWidth, subHeight));
    nodes[3] = new QuadTree(level + 1, sf::IntRect(x + subWidth, y + subHeight, subWidth, subHeight));

    nodes[0]->parent = this;
    nodes[1]->parent = this;
    nodes[2]->parent = this;
    nodes[3]->parent = this;
}

void QuadTree::update() {
    for (std::list<Entity*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        Entity* entity = *(it);
        //pillo su posicion
        sf::Transformable transform = entity->Get<Position*>("Position")->getPosition();
        //actualizo los datos de la colisión con la posición
        entity->Get<Collision*>("Collision")->update(transform);
    }

    //actualizo los hijos
    for (uint i = 0; i < nodes.size(); ++i) {
        if (nodes[i] != nullptr) {
            nodes[i]->update();
        }
    }
    //una vez actualizados, recoloco el árbol (este nodo, los hijos ya se habrán recolocado)
    updateTree();
}

void QuadTree::updateTree() {
    std::list<Entity*>::iterator it = objects.begin();
    while (it != objects.end()) {
        Entity* entity = *it;
        sf::FloatRect rect;
        if (entity->HasID("Velocity")) {
            rect = entity->Get<Collision*>("Collision")->getAABBSwept();
        } else {
            rect = entity->Get<Collision*>("Collision")->getAABB();
        }
        //si esta dentro del recuadro actual
        int index = getIndex(entity->Get<Collision*>("Collision"));
        if (index != -1) {
            if (nodes[index] != nullptr) {
                nodes[index]->insert(entity);
                it = objects.erase(it);
            } else {
                ++it;
            }
        } else {
            if (inside(rect)) {
                ++it;
            } else {
                if (parent != nullptr) {
                    parent->insert(entity);
                    it = objects.erase(it);
                }
            }
        }
    }
}

bool QuadTree::inside(sf::FloatRect rect) {
    if (rect.top >= bounds.top && rect.left >= bounds.left
            && rect.top + rect.height <= bounds.top + bounds.height
            && rect.left + rect.width <= bounds.left + bounds.width) {
        return true;
    } else {
        return false;
    }
}

void QuadTree::getObjects(std::vector<Entity*>& list) {
    for (std::list<Entity*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        Entity* entity = *(it);
        list.push_back(entity);
    }

    for (uint i = 0; i < nodes.size(); ++i) {
        if (nodes[i] != nullptr) {
            nodes[i]->getObjects(list);
        }
    }
}

std::vector<Entity*>* QuadTree::retrieve(std::vector<Entity*>* list, Entity* object) {
    sf::FloatRect rect = object->Get<Collision*>("Collision")->getAABBSwept();
    for (int i = 0; i < 4; ++i) {
        if (nodes[i] != nullptr) {
            sf::FloatRect bounds = nodes[i]->bounds;

            bool touch = false;
            touch = touch | bounds.contains(rect.left, rect.top);
            touch = touch | bounds.contains(rect.left + rect.height, rect.top);
            touch = touch | bounds.contains(rect.left, rect.top + rect.width);
            touch = touch | bounds.contains(rect.left + rect.height, rect.top + rect.width);

            if (touch) {
                nodes[i]->retrieve(list, object);
                continue;
            }

            touch = touch | rect.contains(bounds.left, bounds.top);
            touch = touch | rect.contains(bounds.left + bounds.width, bounds.top);
            touch = touch | rect.contains(bounds.left, bounds.top + bounds.height);
            touch = touch | rect.contains(bounds.left + bounds.width, bounds.top + bounds.height);

            if (touch) {
                nodes[i]->retrieve(list, object);
            }
        }
    }

    for (std::list<Entity*>::iterator it = objects.begin(); it != objects.end(); ++it) {
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
