/* 
 * File:   ParallelTask.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 17:48
 */

#ifndef PARALLELTASK_H
#define	PARALLELTASK_H

#include <SFML/System.hpp>

/**
 * Clase que realiza un trabajo en paralelo
 */
class ParallelTask {
public:
    /**
     * Constructor por defecto
     */
    ParallelTask();
    /*
     * Ejecuta la tarea en paralelo
     */
    void execute();
    /**
     * Indica si ha terminado la tarea
     * @return true si ha finalizado, false al contrario
     */
    bool isFinished();
    /**
     * Devuelve un porcentaje
     * @return porcentaje entre 0 y 1
     */
    float getCompletion();
    
    /**
     * Destructor
     */
    virtual ~ParallelTask();

    /**
     * Método a sobreescribir. En él se codifica la tarea a realizar
     */
    virtual void runTask()=0;
protected:
    /**
     * Hilo donde se ejecuta
     */
    sf::Thread thread;
    /**
     * Variable para comprobar si la tarea ha terminado
     */
    bool finished;
    /**
     * Semáforo para controlar datos entre más de un hilo
     */
    sf::Mutex mutex;
    /**
     * Number between 0 and 1 (percentaje of completion)
     */
    int completion;

};

#endif	/* PARALLELTASK_H */

