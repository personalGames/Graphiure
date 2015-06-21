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
#include "MissionStatus.h"

/**
 * Clase que representa un nivel
 */
class Level : private sf::NonCopyable, Observer {
public:
    /**
     * Constructor explícito
     * @param systemManager gestor de sistemas
     */
    explicit Level(SystemManager& systemManager);
    virtual ~Level();
    
    /**
     * Actualiza el nivel
     * @param dt tiempo entre frame y frame
     */
    void update(sf::Time dt);
    /**
     * Setea el personaje principal
     * @param characterCreated entidad del personaje
     */
    void setCharacter(IdEntity characterCreated);
    /**
     * Dibuja el nivel
     */
    void draw();
    /**
     * Devuelve la cola de comandos
     * @return cola de comandos
     */
    inline CommandQueue& getCommandQueue(){ return commandQueue; }
    /**
     * Procesa la entrada
     */
    bool handleEvent(const sf::Event& event);
    
    /**
     * Setea el jugador (captura de eventos)
     * @param player jugador
     */
    void setPlayer(Player* player) {
        this->player = player;
    }
    
    /**
     * Determina si el nivel ha terminado
     * @return true si el nivel ha terminado
     */
    bool isEnd();
    
    /**
     * Pilla el estado de la misión
     * @return 
     */
    inline MissionStatus getMissionStatus(){
        return status;
    }
    /**
     * Devuelve si se ha de cambiar el nivel o no
     * @return true si se ha de cambiar de nivel
     */
    bool changeLevel();
    /**
     * Devuelve el siguiente nivel que se carga
     * @return 
     */
    std::string* getNextLevel();
    /**
     * Actualiza los subestados del juego cuando hay cambios
     */
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
   /**
    * Id del personaje
    */
    IdEntity idCharacter;
    /**
     * gestor de sistemas
     */
    SystemManager* systemManager;
    /**
     * Sistemas
     */
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
    /**
     * Estado de la mision
     */
    MissionStatus status;
    /**
     * Subestado actual
     */
    SubStateGame* state;
    /**
     * Si se ha de cambiar de nivel
     */
    bool isChangeLevel;
    /**
     * Nombre del nivel siguiente
     */
    std::string* level;
   
};

#endif	/* LEVEL_H */

