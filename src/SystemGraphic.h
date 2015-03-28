/* 
 * File:   SystemGraphic.h
 * Author: dorian
 *
 * Created on 25 de marzo de 2015, 12:59
 */

#ifndef SYSTEMGRAPHIC_H
#define	SYSTEMGRAPHIC_H

#include "ISystem.h"
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "Entity.h"
#include "SceneNode.h"
#include "IDFonts.h"
#include "IDTextures.h"
#include "StructMap.h"
#include "Layer.h"
#include "TileNode.h"
#include "TileMapNode.h"
#include "EntityNode.h"


class SystemGraphic : public ISystem {
public:
    SystemGraphic(sf::RenderWindow& window, ResourceHolder<IDFonts, sf::Font>& fonts,
        ResourceHolder<std::string, sf::Texture>& images);
    virtual ~SystemGraphic();
    

    virtual void initialize();
    virtual void finalize();
    virtual void update(sf::Time dt);
    virtual void updateSecondPart(sf::Time dt);
    virtual void registerEntity(Entity* entity);
    virtual void removedEntity(Entity* entity);

    virtual void execute();

    
    void newScene(StructMap* infoMap);
    
    inline sf::Vector2f getRatio(){
        return ratio;
    }
    
    inline sf::FloatRect getBounds(){
        return worldBounds;
    }
    
    void correctWorldPosition(sf::Vector2f positionCenter);
    
    sf::FloatRect getViewBounds() const;
    
private:
    /**
     * Target where draw
     */
    sf::RenderTarget& target;
    /**
     * View of the map
     */
    sf::View mapView;
    /**
     * Limits of the world
     */
    sf::FloatRect worldBounds;
    sf::Vector2f ratio;
    /**
     * Resources
     */
    ResourceHolder<IDFonts, sf::Font>& fonts;
    ResourceHolder<std::string, sf::Texture>& textures;
    
    /**
     * Scene graph
     */
    SceneNode sceneGraph;
    std::array<SceneNode*, LayerCount> sceneLayers;
};

#endif	/* SYSTEMGRAPHIC_H */

