/* 
 * File:   SystemCollision.h
 * Author: dorian
 *
 * Created on 15 de marzo de 2015, 21:47
 */

#ifndef SYSTEMCOLLISION_H
#define	SYSTEMCOLLISION_H

#include "QuadTree.h"
#include "MessageCollision.h"
#include <queue>
#include "Collision.h"
#include "ISystem.h"
#include "vector"
#include "Position.h"
#include "ActionStack.h"
#include "OnCollision.h"
#include "Velocity.h"
#include "Triangle.h"
#include "DelaunayTriangulation.h"

/**
 * Sistema de colisiones
 */
class SystemCollision : public ISystem {
public:
    /**
     * Constructor. Se le pasa los límites del mapa
     * @param bounds limites del mapa
     */
    SystemCollision(sf::FloatRect bounds);
    SystemCollision();
    virtual ~SystemCollision();
    

    virtual void initialize(){};
    virtual void finalize();
    virtual void update(sf::Time dt);
    virtual void updateSecondPart(sf::Time dt);
    virtual void registerEntity(Entity* entity);
    virtual void removedEntity(Entity* entity);

    /**
     * Crea un nuevo mundo colisionable
     * @param bounds nuevos limites del mapa
     */
    void newWorldCollision(sf::FloatRect bounds);
    /**
     * Limpia el mundo colisionable
     */
    void clear();
    
    /**
     * Busca todas las entidades que colisionan con el cuadrado dado
     * @param query zona a consultar
     * @return lista de entidades que colisionan
     */
    std::vector<Entity*>* query(sf::FloatRect query);
    /**
     * Checkea todas las colisiones que se producen en la región dada
     * las va guardando en una pila
     * @param region zona a consultar colisiones
     */
    void checkCollisions(sf::FloatRect region);
    /**
     * mantiene la entidad dentro del mundo, sin que se salga de los límites
     * lo corrige si es necesario
     * @param entity entidad a comprobar
     */
    void correctInsidePosition(Entity* entity);
    /**
     * Resuelve las colisiones que han quedado en la cola después de comprobar,
     * son delegados en las entidades
     */
    void resolveCollisions();
    
private:
    /**
     * árbol de las colisiones
     */
    QuadTree* tree;
    //pila de colisiones
    std::queue<MessageCollision*> queue;
    /**
     * Triangula las figuras de dos colisionables para afinar la colisión en
     * un tiempo dado
     * @param first un colisionable
     * @param second otro colisionable
     * @param time tiempo en el que presumiblemente han colisionado
     * @return el mensaje de colisión o nullptr si no hay colisión
     */
    MessageCollision* triangulate(Collision* first, Collision* second, float time);
    /**
     * Hace una prueba simple y genérica de si las dos entidades colisionan.
     * Si es así, pasa a mayores comprobaciones
     * @param one una entidad
     * @param two otra entidad
     * @return mensaje de colisión o nullptr si no hay colisión
     */
    MessageCollision* collisionDetection(Entity* one, Entity* two);
    /**
     * COmprueba en que momento habrían colisionado las entidades y manda 
     * triangulizar para afinar la colisión
     * @param one una entidad
     * @param two otra entidad
     * @return mensaje de colisión o nullptr si no hay colisión
     */
    MessageCollision* firstTimeCollision(Entity* one, Entity* two);
    /**
     * Dado dos triángulos que en teoría colisionan,
     * comprueba el colisionado y calcula el mínimo vector de traslado
     * para separar ambos triángulos.
     * @param poly1
     * @param poly2
     * @param detailed true si se desea tener dicho mtv o false si solo se quiere
     * comprobar que colisionan sin hacer cálculos extras
     * @return el mínimo vector de traslado
     */
    MTV checkCollisions(Triangle& poly1, Triangle& poly2, bool detailed);
};

#endif	/* SYSTEMCOLLISION_H */

