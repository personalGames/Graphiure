/* 
 * File:   TileMapNode.h
 * Author: dorian
 *
 * Created on 10 de febrero de 2015, 22:43
 */

#ifndef TILEMAPNODE_H
#define	TILEMAPNODE_H

#include "SceneNode.h"
#include "ResourceHolder.h"
#include <SFML/Graphics.hpp>
#include "StructMap.h"

/**
 * Nodo para el dibujado del mapa
 */
class TileMapNode : public SceneNode {
public:
    /**
     * Constructor
     * @param images
     * @param mapInfo
     * @param width
     * @param heiht
     * @param numberRowsVisible
     * @param numberColumnsVisible
     */
    TileMapNode(const ResourceHolder<std::string, sf::Texture>& images,
        StructMap *mapInfo, int  width, int heiht,
            int numberRowsVisible, int numberColumnsVisible);

    virtual ~TileMapNode();
    /**
     * Prepare the map after initialize the node with details like
     * numbers of rows/columns, size of windows...
     * @param tilesMap
     */
    void prepareMap(const int* tilesMap);
    
    /**
     * Devuelve el ratio de redimensionado
     * @return 
     */
    inline sf::Vector2f getAdjustRatio(){
        return adjustedRatio;
    }
    
    /**
     * Devuelve el tamaño del mapa que se visualiza, dado por el número
     * de columnas y filas con el tamaño del tile en ventana
     * @return 
     */
    sf::Vector2f getSizeMap();
    /**
     * Devuelve el tamaño del tile en pantalla
     * @return 
     */
    inline sf::Vector2f getQuadSize(){
        return quadSize;
    }

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    /**
     * Tamaño del tile original
     */
    sf::Vector2u tileSize;
    /**
     * Número de filas del mapa
     */
    int numberRows;
    /**
     * Número de columnas del mapa
     */
    int numberColumns;
    /**
     * ancho de la ventana
     */
    int widthWindow;
    /**
     * alto de la ventana
     */
    int heightWindow;
    /**
     * Número de columnas visibles
     */
    int numberColumnsVisible;
    /**
     * Número de filas visibles
     */
    int numberRowsVisible;
    /**
     * imagen del tileset
     */
    sf::Texture tileset;
    /**
     * vector de los tiles del mapa, vector bidimensional
     */
    std::vector< std::vector <sf::VertexArray> > chunks;
    /**
     * Tamaño del tile redimensionado
     */
    sf::Vector2f quadSize;
    /**
     * Ratio de redimensionado
     */
    sf::Vector2f adjustedRatio;

};

#endif	/* TILEMAPNODE_H */

