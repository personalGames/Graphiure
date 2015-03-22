/* 
 * File:   Level.cpp
 * Author: dorian
 * 
 * Created on 9 de febrero de 2015, 0:08
 */

#include "Level.h"
#include "TileNode.h"
#include "EntityNode.h"
#include <iostream>

Level::Level(sf::RenderTarget& outputTarget, ResourceHolder<IDFonts, sf::Font>& fonts,
        ResourceHolder<IDTextures, sf::Texture>& images) :
mapView(outputTarget.getDefaultView()), target(outputTarget),
textures(images), fonts(fonts), sceneGraph(), sceneLayers(),
worldBounds(0.f, 0.f, mapView.getSize().x, mapView.getSize().y), ratio(1,1) {

}

void Level::buildScene(StructMap* infoMap) {
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
            10, 10));
    tileMap->prepareMap(infoMap->tiles);
    sf::Vector2f sizeMap=tileMap->getSizeMap();
    worldBounds.height=sizeMap.y;
    worldBounds.width=sizeMap.x;
    ratio=tileMap->getAdjustRatio();
    sceneLayers[Background]->addChild(std::move(tileMap));

    //prepare the underground
    TileNode * tiles(new TileNode(textures,
            infoMap,mapView.getSize().x, mapView.getSize().y,
            10, 10));

    tiles->prepareMap(*(infoMap->underground));
    sceneLayers[Underground]->addChild(std::move(tiles));
}

void Level::setCharacter(Entity* characterCreated) {
    principalCharacter = characterCreated;
    EntityNode* node=new EntityNode(principalCharacter);
    sceneLayers[Ground]->addChild(std::move(node));
}

void Level::setSceneCollision() {

}


void Level::setPointCharacter(int x, int y) {
    int xInitial, yInitial;
    sf::Vector2f window = mapView.getSize();
    xInitial = window.x / 2;
    yInitial = window.y / 2;

    xInitial += x;
    yInitial += y;

    mapView.setCenter(xInitial, yInitial);
}

void Level::draw() {
    target.setView(mapView);
    target.draw(sceneGraph);
}

sf::FloatRect Level::getViewBounds() const {
    sf::Vector2f origin=mapView.getCenter() - mapView.getSize() / 2.f;
    return sf::FloatRect(origin,
            mapView.getSize()+origin);
}


Level::~Level() {

}

void Level::update(sf::Time dt) {
    correctWorldPosition(dt);
    principalCharacter->Set<sf::Vector2f>("Velocity", sf::Vector2f(0,0));

    // Forward commands to scene graph
    while (!commandQueue.isEmpty()) {
        sceneGraph.onCommand(commandQueue.pop(), dt);
    }
    
    //todas estas actualizaciones de sistemas luego se sustituye
    //por el system manager que irá llamando a cada uno de ellos
    // Regular update step
    sceneGraph.update(dt, commandQueue);
    
    collision->update();
    collision->checkCollisions(getViewBounds());
}

void Level::correctWorldPosition(sf::Time dt) {
    sf::Vector2f windowHalf = mapView.getSize() / 2.f;
    sf::Vector2f positionCharacter = principalCharacter->
            Get<sf::Transformable*>("Position")->getPosition();
    
//    std::cout<<positionCharacter.x<<" "<<positionCharacter.y<<std::endl;
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
