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
#include "StructMap.h"
#include "Layer.h"
#include "TileNode.h"
#include "TileMapNode.h"
#include "EntityNode.h"

/**
 * Sistema gráfico
 */
class SystemGraphic : public ISystem {
public:
    /**
     * Constructor
     * @param window ventana de la aplicación
     * @param fonts fuentes de la aplicación
     * @param images imágenes de la aplicación
     */
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

    /**
     * Crea una nueva escena gráfica
     * @param infoMap
     */
    void newScene(StructMap* infoMap);
    
    /**
     * Devuelve el ratio usado para redimensionar
     * @return 
     */
    inline sf::Vector2f getRatio(){
        return ratio;
    }
    
    /**
     * Devuelve los bordes del mapa
     * @return 
     */
    inline sf::FloatRect getBounds(){
        return worldBounds;
    }
    
    /**
     * COrrige la posición de la cámara
     * @param positionCenter posición en la que centrar
     */
    void correctWorldPosition(sf::Vector2f positionCenter);
    
    /**
     * Devuelve los bordes de la vista
     * @return 
     */
    sf::FloatRect getViewBounds() const;
    
    /**
     * Devuelve el target en el que se dibuja
     * @return 
     */
    inline sf::RenderTarget& getTarget() const {
        return target;
    }
    
    /**
     * Devuelve las fuentes que está utilizando para dibujar
     * @return 
     */
    inline ResourceHolder<IDFonts, sf::Font>& getFonts() const {
        return fonts;
    }

    
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
    /**
     * Ratio de redimensionado
     */
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
    /**
     * Nodos dados por la capa
     */
    std::array<SceneNode*, LayerCount> sceneLayers;
    /**
     * Tamaño original del tile en pantalla
     */
    sf::Vector2f sizeTile;
    /**
     * Devuelve el tamaño del tile en pantalla
     * @return 
     */
    inline sf::Vector2f getSizeTile() const {
        return sizeTile;
    }

};

#endif	/* SYSTEMGRAPHIC_H */

