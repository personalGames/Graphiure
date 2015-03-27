/* 
 * File:   Level.h
 * Author: dorian
 *
 * Created on 9 de febrero de 2015, 0:08
 */

#ifndef LEVEL_H
#define	LEVEL_H

#include "CommandQueue.h"
#include "SceneNode.h"
#include "Layer.h"
#include "ResourceHolder.h"
#include "IDFonts.h"
#include "IDTextures.h"
#include "TileMapNode.h"
#include "IXMLParser.h"
#include "Entity.h"
#include "StructMap.h"
#include "Entity.h"
#include "SystemCollision.h"
#include "SystemManager.h"
#include "SystemGraphic.h"
#include "SystemObjectsGame.h"
#include "SystemCommand.h"


class Level : private sf::NonCopyable {
public:
    explicit Level(SystemManager& systemManager);
    virtual ~Level();
    
    void update(sf::Time dt);
    void setCharacter(IdEntity characterCreated);
    void draw();
    
    inline CommandQueue& getCommandQueue(){ return commandQueue; }
    
private:
   
    /**
     * Queue of commands
     */
    CommandQueue commandQueue;
    
    /**
     * Position where character will appear
     */
    sf::Vector2f spawnPosition;
   
    IdEntity idCharacter;
    SystemManager* systemManager;
    
    SystemObjectsGame* objectsGame;
    SystemGraphic* graphics;
    SystemCollision* collision;
    SystemCommand* commands;
   
};

#endif	/* LEVEL_H */

