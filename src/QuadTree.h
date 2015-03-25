/* 
 * File:   QuadTree.h
 * Author: dorian
 *
 * Created on 15 de marzo de 2015, 18:20
 */

#ifndef QUADTREE_H
#define	QUADTREE_H

#include <vector>
#include "Collision.h"
#include <list>
#include "Entity.h"
#include <SFML/Graphics.hpp>

const int MAX_OCCUPANTS = 6;
const int MIN_OCCUPANTS = 1;

const int MAX_LEVELS = 20;

class QuadTree {
public:
    QuadTree(int level, sf::IntRect bounds);
    QuadTree(int level, sf::FloatRect bounds);
    QuadTree(int level);

    void clear();
    void insert(Entity* objectNew);
    bool remove(Entity* object);
    std::vector<Entity*>* retrieve(std::vector<Entity*>* list, Entity* object);
    void update();
    void updateTree();
    void getObjects(std::vector<Entity*>& list);
    QuadTree* getNodeRegion(sf::FloatRect region);
//    void toString();

private:
    void split();
    int getIndex(Collision* collision);
    int getIndex(sf::FloatRect rect);
    bool inside(sf::FloatRect rect);

private:
    int level;
    std::list<Entity*> objects;
    sf::FloatRect bounds;
    QuadTree* parent;
    std::vector<QuadTree*> nodes;
};

#endif	/* QUADTREE_H */

