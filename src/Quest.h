/* 
 * File:   Quest.h
 * Author: dorian
 *
 * Created on 7 de mayo de 2015, 11:36
 */

#ifndef QUEST_H
#define	QUEST_H

#include "PartQuest.h"
#include <SFML/System/Time.hpp>
#include <vector>
#include <algorithm>
#include <SFML/System/String.hpp>

/**
 * Representa una misión
 */
class Quest {
public:
    /**
     * Constructor para una misión sin limite de tiempo (tiempo=0)
     * @param id identificador de la mision
     * @param text texto descriptivo de la mision
     */
    Quest(int id, sf::String* text);
    /**
     * Constructor para una misión con limite de tiempo
     * @param id identificador de la mision
     * @param text texto descriptivo de la mision
     * @param time el límite de tiempo para la mision. SI es 0, no hay límite
     */
    Quest(int id, sf::String* text, sf::Time time);
    /**
     * Constructor copia
     * @param orig
     */
    Quest(const Quest& orig);
    virtual ~Quest();
    
    /**
     * Añade una parte más a la mision
     * @param part parte de mision
     */
    void addPartQuest(PartQuest* part);
    
    /**
     * Devuelve el tiempo limite que dispone
     * @return tiempo limite
     */
    inline sf::Time getTime() const {
        return time;
    }

    /**
     * Setea el tiempo limite
     * @param time
     */
    inline void setTime(sf::Time time) {
        this->time = time;
    }
    
    /**
     * Devuelve la descripción de la mision
     * @return descripcion de la mision
     */
    inline sf::String* getText(){
        return textQuest;
    }

    /**
     * Indica si está finalizado
     * @return true si esta finalizado
     */
    bool isFinished();
    /**
     * Lista de misiones que se activarán cuando esta mision se termine
     * @return lista de misiones a activar al finalizar
     */
    std::vector<int> onFinished();
    /**
     * Actualiza la mision
     * @param dt tiempo entre frame y frame
     */
    void update(sf::Time dt);
    
    /**
     * Añade el identificador de una misión que se activará cuando esta misión
     * termine
     * @param id identificador de la mision que se activará
     */
    inline void addQuestOpen(int id){
        idQuestToOpen.push_back(id);
    }
    
    /**
     * Elimina una misión dentro de las que se activan al finalizar esta mision
     * @param id identificador de la mision a borrar
     */
    inline void removeQuestOpen(int id);
    
    /**
     * Devuelve el id de la mision
     * @return id de la mision
     */
    int getId() const {
        return id;
    }

    /**
     * Setea el id de la mision
     * @param id id nueva de la mision
     */
    void setId(int id) {
        this->id = id;
    }
    
    /**
     * Indica si la mision está activa
     * @return true si esta activa/abierta
     */
    bool isOpened() const {
        return opened;
    }

    /**
     * Setea si la mision esta activa
     * @param opened true para activar la mision, false para dejarla inactiva
     */
    void setOpened(bool opened) {
        this->opened = opened;
    }
    
    /**
     * Indica si las partes de la mision se hacen en orden o no
     * @return true si las partes de la mision se tienen que hacer en orden
     */
    bool isInOrder() const {
        return inOrder;
    }

    /**
     * Setea si las partes de la mision se hacen en orden
     * @param inOrder true si se hacen en orden
     */
    void setInOrder(bool inOrder) {
        this->inOrder = inOrder;
    }

    /**
     * Devuelve las partes de la que consta la misión
     * @return lista de partes de la mision
     */
    inline const std::vector<PartQuest*>& getPartQuests(){
        return list;
    }
    
private:
    /**
     * Identificador de la mision
     */
    int id;
    /**
     * Si esta abierta la mision para cumplirla
     */
    bool opened;
    /**
     * Lista de partes de mision por cumplir
     */
    std::vector<PartQuest*> list;
    /**
     * Lista de partes de mision cumplidas
     */
    std::vector<PartQuest*> doneList;
    /**
     * TIempo limite
     */
    sf::Time time;
    /**
     * tiempo para controlar el límite pasado
     */
    sf::Time timer;
    /**
     * Lista de misiones a abrir cuando se complete la mision
     */
    std::vector<int> idQuestToOpen;
    /**
     * Descripción de la misión
     */
    sf::String* textQuest;
    /**
     * Indica si las partes se hacen en orden o no
     */
    bool inOrder;
};

#endif	/* QUEST_H */

