/* 
 * File:   Level.cpp
 * Author: dorian
 * 
 * Created on 9 de febrero de 2015, 0:08
 */

#include "Level.h"


Level::Level(sf::RenderTarget& outputTarget, ResourceHolder<IDFonts, sf::Font>& fonts) :
        target(outputTarget),  mapView(outputTarget.getDefaultView()),
        textures(), fonts(fonts), sceneGraph(), sceneLayers(), worldBounds(0.f, 0.f, mapView.getSize().x, 2000.f) {
    loadTextures();
    buildScene();
}

void Level::buildScene() {
    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode* layer = new SceneNode();

        sceneLayers[i] = std::move(layer);
        sceneGraph.addChild(std::move(layer));
    }
    
    //prepare the background
    
}

void Level::draw() {
    target.setView(mapView);
    target.draw(sceneGraph);
}

sf::FloatRect Level::getViewBounds() const {
        return sf::FloatRect(mapView.getCenter() - mapView.getSize() / 2.f, mapView.getSize());
}

void Level::loadTextures() {

}

void Level::update(sf::Time dt) {
    //nothing by now
}

Level::~Level() {

}
