/* 
 * File:   Questeable.h
 * Author: dorian
 *
 * Created on 7 de mayo de 2015, 12:54
 */

#ifndef QUESTEABLE_H
#define	QUESTEABLE_H

#include "PartQuest.h"

/**
 * Clase para la propiedad questeable
 */
class Questeable {
public:
    /**
     * Constructor
     * @param id identificador de la misión
     */
    Questeable(int id);
    Questeable(const Questeable& orig);
    virtual ~Questeable();
    /**
     * Añade la parte de misión asociada
     * @param quest parte de misión
     */
    void addPartQuest(PartQuest* quest);
    /**
     * Devuelve el identificador de la misión
     * @return 
     */
    inline int getIdQuest() const {
        return idQuest;
    }
    
    /**
     * Devuelve la lista de partes de misión asociadas
     * @return 
     */
    inline const std::vector<PartQuest*>& getPartQuest(){
        return quest;
    }
    
private:
    /**
     * lista de partes de misiones
     */
    std::vector<PartQuest*> quest;
    /**
     * Identificador de mision asociado
     */
    int idQuest;

};

#endif	/* QUESTEABLE_H */

