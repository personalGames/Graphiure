/* 
 * File:   LoadingLevel.h
 * Author: dorian
 *
 * Created on 11 de febrero de 2015, 23:58
 */

#ifndef LOADINGLEVEL_H
#define	LOADINGLEVEL_H

#include "ParallelTask.h"
#include "Levels.h"
#include "Level.h"
#include "ResourceHolder.h"
#include "SystemManager.h"
#include "Context.h"

/**
 * Tarea paralela para cargar un nivel
 */
class LoadingLevel : public ParallelTask{
public:
    /**
     * Constructor
     * @param level nombre/ruta del nivel a cargar
     * @param context contexto de la aplicación
     */
    LoadingLevel(std::string* level, Context* context);
    virtual ~LoadingLevel();
    
    virtual void runTask();

private:
    /**
     * Nombre/ruta del nivel a cargar
     */
    std::string* level;
    /**
     * PUntero donde guardar el nivel cargado
     */
    Level* levelToLoad;
    /**
     * Recursos de imágenes
     */
    ResourceHolder<std::string, sf::Texture>* textures;
    /**
     * Gestor de sistemas
     */
    SystemManager* systemManager;
    /**
     * Contexto
     */
    Context* context;
};

#endif	/* LOADINGLEVEL_H */

