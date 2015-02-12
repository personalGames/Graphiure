/* 
 * File:   Level.cpp
 * Author: dorian
 * 
 * Created on 9 de febrero de 2015, 0:08
 */

#include "Level.h"
#include "TileMapNode.h"
#include "Context.h"
#include <iostream>

Level::Level(sf::RenderTarget& outputTarget, ResourceHolder<IDFonts, sf::Font>& fonts,
        ResourceHolder<IDTextures, sf::Texture>& images) :
        target(outputTarget),  mapView(outputTarget.getDefaultView()),
        textures(images), fonts(fonts), sceneGraph(), sceneLayers(), worldBounds(0.f, 0.f, mapView.getSize().x, 2000.f) {
    
}

void Level::buildScene() {
    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode* layer = new SceneNode();

        sceneLayers[i] = std::move(layer);
        sceneGraph.addChild(std::move(layer));
    }
    
    //prepare the background
    const int tiles[] = {
        55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
        55, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 55,
        55, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 1, 1, 0, 3, 3, 3, 7, 7, 7, 1, 1, 1, 2, 0,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 0, 1, 0, 3, 0, 2, 2, 7, 7, 1, 1, 1, 1, 2,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 0, 1, 0, 3, 0, 2, 2, 7, 7, 1, 1, 1, 1, 2,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 0, 1, 0, 3, 0, 2, 2, 7, 7, 1, 1, 1, 1, 2,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 0, 1, 0, 3, 0, 2, 2, 7, 7, 1, 1, 1, 1, 2,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 0, 1, 0, 3, 0, 2, 2, 7, 7, 1, 1, 1, 1, 2,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 0, 1, 0, 3, 0, 2, 2, 7, 7, 1, 1, 1, 1, 2,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 0, 1, 0, 3, 0, 2, 2, 7, 7, 1, 1, 1, 1, 2,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 0, 1, 0, 3, 0, 2, 2, 7, 7, 1, 1, 1, 1, 2,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 0, 1, 0, 3, 0, 2, 2, 7, 7, 1, 1, 1, 1, 2,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 0, 1, 0, 3, 0, 2, 2, 7, 7, 1, 1, 1, 1, 2,1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 55,
        55, 0, 1, 0, 3, 0, 2, 2, 7, 7, 1, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,55,
        55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
    };
    TileMapNode* tileMap(new TileMapNode(textures, 
            30, 30, 
            mapView.getSize().x, mapView.getSize().y,
            15,15));
    tileMap->prepareMap(tiles);
    sceneLayers[Background]->addChild(std::move(tileMap));
    setPointCharacter(spawnPosition.x, spawnPosition.y);
}

void Level::setPointCharacter(int x, int y){
    int xInitial, yInitial;
    sf::Vector2f window=mapView.getSize();
    xInitial=window.x/2;
    yInitial=window.y/2;
    
    xInitial+=x;
    yInitial+=y;
    
    mapView.setCenter(xInitial, yInitial);
}

void Level::draw() {
    target.setView(mapView);
    target.draw(sceneGraph);
}

sf::FloatRect Level::getViewBounds() const {
        return sf::FloatRect(mapView.getCenter() - mapView.getSize() / 2.f, mapView.getSize());
}


void Level::update(sf::Time dt) {
    //nothing by now
}

Level::~Level() {

}
