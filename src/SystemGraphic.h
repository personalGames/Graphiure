/* 
 * File:   SystemGraphic.h
 * Author: dorian
 *
 * Created on 25 de marzo de 2015, 12:59
 */

#ifndef SYSTEMGRAPHIC_H
#define	SYSTEMGRAPHIC_H

#include "ISystem.h"


class SystemGraphic : public ISystem {
public:
    SystemGraphic();
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
    
private:
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
     * Limits of the world
     */
    sf::FloatRect worldBounds;
    sf::Vector2f ratio;
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
};

#endif	/* SYSTEMGRAPHIC_H */

