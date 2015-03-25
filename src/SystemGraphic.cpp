/* 
 * File:   SystemGraphic.cpp
 * Author: dorian
 * 
 * Created on 25 de marzo de 2015, 12:59
 */

#include "SystemGraphic.h"

SystemGraphic::SystemGraphic() {

}

void SystemGraphic::finalize() {

}

void SystemGraphic::initialize() {

}

void SystemGraphic::newScene(StructMap* infoMap) {
    
    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode* layer = new SceneNode();

        sceneLayers[i] = std::move(layer);
        sceneGraph.addChild(std::move(layer));
    }


    //prepare the principal background
    TileMapNode * tileMap(new TileMapNode(textures,
            infoMap,
            mapView.getSize().x, mapView.getSize().y,
            20, 20));
    tileMap->prepareMap(infoMap->tiles);
    sf::Vector2f sizeMap=tileMap->getSizeMap();
    worldBounds.height=sizeMap.y;
    worldBounds.width=sizeMap.x;
    ratio=tileMap->getAdjustRatio();
    sceneLayers[Background]->addChild(std::move(tileMap));

    //prepare the underground
    TileNode * tiles(new TileNode(textures,
            infoMap,mapView.getSize().x, mapView.getSize().y,
            20, 20));

    tiles->prepareMap(*(infoMap->underground));
    sceneLayers[Underground]->addChild(std::move(tiles));
}

void SystemGraphic::registerEntity(Entity* entity) {
    if(entity->HasID("Drawable")){
        EntityNode* node=new EntityNode(entity);
        sceneLayers[Ground]->addChild(std::move(node));
    }
}

void SystemGraphic::removedEntity(Entity* entity) {

}

void SystemGraphic::update(sf::Time dt) {

}

void SystemGraphic::execute() {
    target.setView(mapView);
    target.draw(sceneGraph);
}


void SystemGraphic::updateSecondPart(sf::Time dt) {

}

SystemGraphic::~SystemGraphic() {

}



sf::FloatRect SystemGraphic::getViewBounds() const {
    sf::Vector2f origin=mapView.getCenter() - mapView.getSize() / 2.f;
    return sf::FloatRect(origin,
            mapView.getSize()+origin);
}

void SystemGraphic::correctWorldPosition(sf::Vector2f positionCenter) {
    sf::Vector2f windowHalf = mapView.getSize() / 2.f;
    sf::Vector2f positionCharacter = positionCenter;
    
    sf::Vector2f move(0, 0);

    if (positionCharacter.x > windowHalf.x) {
        if (positionCharacter.x < (worldBounds.width - windowHalf.x)) {
            move.x = positionCharacter.x;
        } else {
            move.x = worldBounds.width - windowHalf.x;
        }

    } else {
        move.x = windowHalf.x;
    }

    if (positionCharacter.y > windowHalf.y) {
        if (positionCharacter.y < (worldBounds.height - windowHalf.y)) {
            move.y = positionCharacter.y;
        } else {
            move.y = worldBounds.height - windowHalf.y;
        }

    } else {
        move.y = windowHalf.y;
    }

    mapView.setCenter(move);
}
