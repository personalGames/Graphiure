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
#include "Velocity.h"
#include "ImportSystems.h"
#include "Player.h"
#include "Observer.h"
#include "SubStateGame.h"
#include "ConversationState.h"

class Level : private sf::NonCopyable, Observer {
public:
    explicit Level(SystemManager& systemManager);
    virtual ~Level();
    
    void update(sf::Time dt);
    void setCharacter(IdEntity characterCreated);
    void draw();
    
    inline CommandQueue& getCommandQueue(){ return commandQueue; }
    
    bool handleEvent(const sf::Event& event);
    
    void setPlayer(Player* player) {
        this->player = player;
    }
    

    virtual void update();

    
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
    SystemMovement* movement;
    SystemQuest* quests;
    
    /**
     * Player
     */
    Player* player;
    
    
    SubStateGame* state;
   
};

#endif	/* LEVEL_H */

