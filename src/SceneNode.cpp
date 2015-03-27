/* 
 * File:   SceneNode.cpp
 * Author: dorian
 * 
 * Created on 12 de diciembre de 2014, 23:09
 */


#include "SceneNode.h"

SceneNode::SceneNode(Category category) : children(), parent(nullptr), defaultCategory(category) {
}

SceneNode::SceneNode() : children(), parent(nullptr), defaultCategory(Category::NONE) {
}

SceneNode::~SceneNode() {

}

void SceneNode::addChild(SceneNode* child) {
    //set the parent of the child
    child->parent = this;
    children.push_back(std::move(child));
}

SceneNode* SceneNode::removeChild(const SceneNode& node) {
    SceneNode* result = nullptr;

    //using lambdas to find the child. Comparing with the pointers
    auto found = std::find_if(children.begin(), children.end(),
            [&] (SceneNode* & p) -> bool {
                return p == &node;
            }
    );

    //if found...
    if (found != children.end()) {
        //move the result instead of copy
        result = std::move(*found);
        result->parent = nullptr;
        children.erase(found);
    }

    return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Apply transform of current node
    states.transform *= getTransform();

    // Draw node and children with changed transform
    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    // Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const SceneNode* child : children) {
        child->draw(target, states);
    }
}

void SceneNode::update(sf::Time dt, CommandQueue& commands) {
    updateCurrent(dt, commands);
    updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time delta, CommandQueue&) {
    
}

void SceneNode::updateChildren(sf::Time delta, CommandQueue& commands) {
    for (SceneNode* child : children) {
        child->update(delta, commands);
    }
}

sf::Transform SceneNode::getWorldTransform() const {
    //initialize a transform
    sf::Transform transform = sf::Transform::Identity;

    //iterate the scene graph to the root to get the absolute transforms
    for (const SceneNode* node = this; node != nullptr; node = node->parent) {
        transform = node->getTransform() * transform;
    }

    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const {
    return getWorldTransform() * sf::Vector2f();
}

void SceneNode::onCommand(const Command& command, sf::Time delta) {
    // Command current node, if category matches
//    if ((command.category & this->getCategory())>=1) {
//        command.action(*this, delta);
//    }
//
//    // Propagate command to children
//    for (SceneNode* child : children) {
//        child->onCommand(command, delta);
//    }
}

unsigned int SceneNode::getCategory() const {
    return defaultCategory;
}

void SceneNode::removeWrecks() {
    // Remove all children which request so
    auto wreckfieldBegin = std::remove_if(children.begin(), children.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
    children.erase(wreckfieldBegin, children.end());

    // Call function recursively for all remaining children
    std::for_each(children.begin(), children.end(), std::mem_fn(&SceneNode::removeWrecks));
}

sf::FloatRect SceneNode::getBoundingRect() const {
    return sf::FloatRect();
}

bool SceneNode::isMarkedForRemoval() const {
    // By default, remove node if entity is destroyed
    return isDestroyed();
}

bool SceneNode::isDestroyed() const {
    // By default, scene node needn't be removed
    return false;
}