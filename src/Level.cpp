/* 
 * File:   Level.cpp
 * Author: dorian
 * 
 * Created on 9 de febrero de 2015, 0:08
 */

#include "Level.h"

Level::Level(sf::RenderTarget& outputTarget, ResourceHolder<IDFonts, sf::Font>& fonts,
        ResourceHolder<IDTextures, sf::Texture>& images) :
mapView(outputTarget.getDefaultView()), target(outputTarget),
textures(images), fonts(fonts), sceneGraph(), sceneLayers(),
worldBounds(0.f, 0.f, mapView.getSize().x, 2000.f) {

}

void Level::buildScene(StructMap* infoMap, Character* characterCreated) {
    principalCharacter = characterCreated;

    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode* layer = new SceneNode();

        sceneLayers[i] = std::move(layer);
        sceneGraph.addChild(std::move(layer));
    }

    //prepare the underground
    std::vector< sf::Vector3i >* underground = infoMap->underground;
    int i = underground->size();
    while (i > 0) {
        //        sceneLayers[Underground]->addChild();
        --i;
    }


    //prepare the principal background
    TileMapNode * tileMap(new TileMapNode(textures,
            infoMap,
            mapView.getSize().x, mapView.getSize().y,
            20, 20));
    tileMap->prepareMap(infoMap->tiles);
    sizeMap = tileMap->getSizeMap();
    sceneLayers[Background]->addChild(std::move(tileMap));

    sceneLayers[Ground]->addChild(std::move(principalCharacter));



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
    return sf::FloatRect(mapView.getCenter() - mapView.getSize() / 2.f, mapView.getSize());
}

Level::~Level() {

}

void Level::update(sf::Time dt) {
    correctWorldPosition(dt);
    principalCharacter->setVelocity(0.f, 0.f);

    // Forward commands to scene graph
    while (!commandQueue.isEmpty()) {
        sceneGraph.onCommand(commandQueue.pop(), dt);
    }
    // Regular update step
    sceneGraph.update(dt, commandQueue);
}

void Level::correctWorldPosition(sf::Time dt) {
    sf::Vector2f windowHalf = mapView.getSize() / 2.f;
    sf::Vector2f center = mapView.getCenter();
    sf::Vector2f positionCharacter = principalCharacter->getPosition();
    sf::Vector2f move(0,0);
    
    if(positionCharacter.x>windowHalf.x){
        if(positionCharacter.x<(sizeMap.x-windowHalf.x)){
            move.x=positionCharacter.x;
        }else{
            move.x=sizeMap.x-windowHalf.x;
        }
        
    }else{
        move.x=windowHalf.x;
    }
    
    if(positionCharacter.y>windowHalf.y){
        if(positionCharacter.y<(sizeMap.y-windowHalf.y)){
            move.y=positionCharacter.y;
        }else{
            move.y=sizeMap.y-windowHalf.y;
        }
        
    }else{
        move.y=windowHalf.y;
    }
    
    //move=move+windowHalf;
    mapView.setCenter(move);
}
