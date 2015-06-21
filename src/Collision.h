/* 
 * File:   Collision.h
 * Author: dorian
 *
 * Created on 15 de marzo de 2015, 21:20
 */

#ifndef COLLISION_H
#define	COLLISION_H

#include <SFML/Graphics.hpp>

#include "TypeCollision.h"

/**
 * Clase colisión, define una figura de colisión
 */
class Collision {
public:
    /**
     * Constructor por defecto
     */
    Collision();
    virtual ~Collision();

    /**
     * Añade vertice al colisionable
     * @param vertex vértice
     */
    void addVertice(sf::Vertex & vertex);
    /**
     * Añade un array de vértices
     * @param array de vértices
     */
    void addArrayVertex(sf::VertexArray& array);
    /**
     * Setea el array de vértices
     * @param array
     */
    void setArrayVertex(sf::VertexArray* array);
    /**
     * Actualiza los vértices con la posición, rotación y escalado especificados
     * @param transform posición, rotación y escalado
     */
    void update(sf::Transformable& transform);
    /**
     * Aplica un ratio de redimensionado a los vértices
     * @param ratio
     */
    void applyRatio(sf::Vector2f ratio);
    /**
     * Devuelve las transformadas (posición, rotación y escalado)
     * @return transformada
     */
    inline sf::Transformable getTransform() {
        return transform;
    }
    
    /**
     * Devuelve el tipo de colisión
     * @return tipo de colisión
     */
    TypeCollision getType() const {
        return type;
    }

    /**
     * Setea el tipo de colisión
     * @param type tipo de colisión
     */
    void setType(TypeCollision type) {
        this->type = type;
    }
    
    /**
     * Devuelve el rectángulo que contiene a los vértices
     * @return rectángulo que contiene a los vértices
     */
    sf::FloatRect getAABB();
    /**
     * Entre la posición anterior y la actual, devuelve el rectángulo 
     * que contiene a los vértices en el tiempo especificado
     * @param time tiempo entre las posiciones
     * @return rectángulo en el tiempo especificado
     */
    sf::FloatRect getAABB(float time);
    /**
     * Devuelve el rectángulo que contiene a los vértices en la posición anterior
     * @return rectángulo que contiene a los vértices en la posición anterior
     */
    sf::FloatRect getPreviousAABB();
    /**
     * Entre la posición anterior y la actual, devuelve el rectángulo 
     * formado entre los rectángulos de la posición anterior y la actual
     * @return rectángulo entre ambas posiciones
     */
    sf::FloatRect getAABBSwept();
    
    /**
     * Vértices de la figura colisionable
     */
    sf::VertexArray* vertices;
private:
    /**
     * Tipo de colisión
     */
    TypeCollision type;
    /**
     * Transformada actual
     */
    sf::Transformable transform;
    /**
     * Transformada previa
     */
    sf::Transformable previousTransform;
    
};

#endif	/* COLLISION_H */

