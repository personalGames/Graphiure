/* 
 * File:   QuadTree.h
 * Author: dorian
 *
 * Created on 15 de marzo de 2015, 18:20
 */

#ifndef QUADTREE_H
#define	QUADTREE_H

#include <vector>
#include "Collision.h"
#include <list>
#include "Entity.h"
#include <SFML/Graphics.hpp>

const int MAX_OCCUPANTS = 6;
const int MIN_OCCUPANTS = 1;

const int MAX_LEVELS = 20;

/**
 * Estructura de árbol cuaternario para estructurar por área los elementos colisionables
 * El quadtree es un nodo del árbol
 */
class QuadTree {
public:
    /**
     * Crea un nodo de un determinado nivel y de una determinada área limitada
     * @param level nivel
     * @param bounds área que cubre el nodo
     */
    QuadTree(int level, sf::IntRect bounds);
    /**
     * Crea un nodo de un determinado nivel y de una determinada área limitada
     * @param level nivel
     * @param bounds área que cubre el nodo
     */
    QuadTree(int level, sf::FloatRect bounds);
    /**
     * Crea un nodo de un determinado nivel y sin especificar área
     * @param level
     */
    QuadTree(int level);
    virtual ~QuadTree();

    /**
     * Limpia el área
     */
    void clear();
    /**
     * Inserta una entidad. Si se permite y encaja mejor en algún nodo hijo, lo
     * delega a los hijos. SI no encaja en el nodo y tiene padre, se lo pasa al padre
     * @param objectNew entidad a guardar
     * @param notChild por defecto false, permite que delege en el hijo si encaja mejor,
     *  true para no dar a los hijos
     */
    void insert(Entity* objectNew, bool notChild=false);
    /**
     * Elimina una entidad
     * @param object entidad a eliminar
     * @return true si se ha eliminado con éxito
     */
    bool remove(Entity* object);
    /**
     * Devuelve una lista de todas las entidades que colisionan con la entidad dada
     * @param list lista donde guardar entidades colisionadas
     * @param object entidad al que testear colisiones
     * @return lista con las entidades que colisionan
     */
    std::vector<Entity*>* retrieve(std::vector<Entity*>* list, Entity* object);
    /**
     * Devuelve una lista de todas las entidades que están en la zona dada
     * @param list lista donde guardar entidades de la zona
     * @param rect zona a testear
     * @return lista con las entidades que tocan la zona
     */
    std::vector<Entity*>* retrieve(std::vector<Entity*>* list, sf::FloatRect rect);
    /**
     * Actualiza el árbol, recolocando las entidades si es necesario
     */
    void update();
    /**
     * Devuelve las entidades del nodo y sus hijos
     * @param list lista de entidades del subárbol a partir de este nodo
     */
    void getObjects(std::vector<Entity*>& list);
    /**
     * Devuelve el nodo más profundo que contiene la región especificada
     * @param region región consultada
     * @return nodo que contiene la región o nullptr si no hay nodo que lo contenga
     */
    QuadTree* getNodeRegion(sf::FloatRect region);
    /**
     * Devuelve los límites/región que contiene el nodo
     * @return rectángulo con los límites de la región que contiene el nodo
     */
    inline sf::FloatRect getBounds() const {
        return bounds;
    }

    /**
     * Imprime el árbol a partir de este nodo
     */
    void toString();

private:
    /**
     * DIvide un nodo en cuatro subnodos
     */
    void split();
    /**
     * Devuelve el nodo hijo que contiene el colisionable dado
     * @param collision colisionable
     * @return indice del nodo hijo que contiene la región del colisionable, o -1 si
     * ningún hijo puede contenerlo
     */
    int getIndex(Collision* collision);
    /**
     * Devuelve el nodo hijo que contiene la zona dada
     * @param rect zona dada
     * @return indice del nodo hijo que contiene la región, o -1 si
     * ningún hijo puede contenerlo
     */
    int getIndex(sf::FloatRect rect);
    /**
     * Comprueba si la zona encaja totalmente dentro del nodo 
     * (es decir, todos sus vértices están contenidos)
     * @param rect zona a testear
     * @return true si todos sus vértices están dentro del nodo
     */
    bool inside(sf::FloatRect rect);
    /**
     * Función auxiliar para recolocar las entidades en el árbol
     */
    void updateTree();

private:
    /**
     * Nivel del árbol
     */
    int level;
    /**
     * Lista de entidades del nodo
     */
    std::list<Entity*> objects;
    /**
     * Límites del nodo
     */
    sf::FloatRect bounds;
    /**
     * Nodo padre
     */
    QuadTree* parent;
    /**
     * Nodos hijos
     */
    std::vector<QuadTree*> nodes;
};

#endif	/* QUADTREE_H */

