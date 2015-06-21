/* 
 * File:   TileMapNode.h
 * Author: dorian
 *
 * Created on 10 de febrero de 2015, 22:43
 */

#ifndef TILENODE_H
#define	TILENODE_H

#include "SceneNode.h"
#include "ResourceHolder.h"
#include <SFML/Graphics.hpp>
#include "StructMap.h"

/**
 * Clase que representa un Tile o varios del mapa
 */
class TileNode : public SceneNode {
public:
    /**
     * 
     * @param images texturas de la aplicación
     * @param mapInfo estructura con la información del mapa
     * @param width ancho del mapa
     * @param heiht alto del mapa
     * @param numberRowsVisible número de filas visibles en pantalla
     * @param numberColumnsVisible número de columnas visibles en pantalla
     */
    TileNode(const ResourceHolder<std::string, sf::Texture>& images,
            StructMap *mapInfo, int width, int heiht,
            int numberRowsVisible, int numberColumnsVisible);

    /**
     * Destructor
     */
    virtual ~TileNode();

    /**
     * Prepare the map after initialize the node with details like
     * numbers of rows/columns, size of windows...
     * @param tilesMap vector con los tiles. Cada tile está representado en un
     *  vector de tres enteros indicando posición x,y y el tercer entero representa
     * el tile a dibujar
     */
    void prepareMap(const std::vector< sf::Vector3i >& tilesMap);

    /**
     * Devuelve el tamaño del mapa
     * @return vector de dos números representando el tamaño del mapa
     */
    sf::Vector2f getSizeMap();

    /**
     * Devuelve el tamaño del tile visualizado en pantalla
     * @return vector de dos números representando el tamaño
     */
    inline sf::Vector2f getQuadSize() {
        return quadSize;
    }

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:

    /**
     * Estructura para un tile
     */
    struct Tile {
        /**
         * Posición
         */
        int x, y;
        /**
         * Vértices definiendo el área que se copia para dibujo de una imagen
         */
        sf::VertexArray vertices;

        /**
         * Constructor
         * @param x posición x del tile
         * @param y posición y del tile
         * @param vertices vertices que definen la zona de la imagen asociada al tile
         */
        Tile(int x, int y, sf::VertexArray& vertices) :
            x(x), y(y), vertices(vertices) {
        }

        /**
         * Constructor copia
         * @param tile
         */
        Tile(const Tile &tile) :
            x(tile.x), y(tile.y), vertices(tile.vertices) {
        }
    };

    /**
     * Tamaño original del tile en la imagen
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
     * Ancho de la ventana
     */
    int widthWindow;
    /**
     * Alto de la ventana
     */
    int heightWindow;
    /**
     * Número de columnas visible
     */
    int numberColumnsVisible;
    /**
     * Número de filas visible
     */
    int numberRowsVisible;
    /**
     * Imagen donde se obtiene las imágenes de tiles
     */
    sf::Texture tileset;
    /**
     * vector de tiles
     */
    std::vector< std::vector <Tile> > chunks;
    /**
     * Tamaño del tile en ventana
     */
    sf::Vector2f quadSize;



};

#endif	/* TILENODE_H */

