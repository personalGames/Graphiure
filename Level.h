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

class Level : private sf::NonCopyable{
public:
    explicit Level(sf::RenderTarget& outputTarget, ResourceHolder<IDFonts, sf::Font>& fonts,
            ResourceHolder<IDTextures, sf::Texture>& images);
    virtual ~Level();
    
    void update(sf::Time dt);
    void draw();
    void buildScene();
    inline CommandQueue& getCommandQueue(){ return commandQueue; }
    
private:
    void loadTextures();
    void setPointCharacter(int x, int y);
    sf::FloatRect getViewBounds() const;
    
private:
    /**
     * View of the map
     */
    sf::View mapView;
    /**
     * Target where draw
     */
    sf::RenderTarget& target;
    /**
     * Resources
     */
    ResourceHolder<IDTextures, sf::Texture> textures;
    ResourceHolder<IDFonts, sf::Font>& fonts;
    
    /**
     * Scene graph
     */
    SceneNode sceneGraph;
    std::array<SceneNode*, LayerCount> sceneLayers;
    
    /**
     * Queue of commands
     */
    CommandQueue commandQueue;
    
    /**
     * Limits of the world
     */
    sf::FloatRect worldBounds;
    /**
     * Position where character will appear
     */
    sf::Vector2f spawnPosition;
    
    
};

#endif	/* LEVEL_H */

