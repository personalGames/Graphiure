/* 
 * File:   FactoryGameObjects.h
 * Author: dorian
 *
 * Created on 30 de marzo de 2015, 21:06
 */

#ifndef FACTORYGAMEOBJECTS_H
#define	FACTORYGAMEOBJECTS_H

#include "GameObjects.h"
#include <string>
#include <memory>
#include "StaticBlock.h"
#include "Hole.h"

/**
 * 
 */
namespace FactoryGameObjects{
    /**
     * Devuelve la instancia de la clase que crea el tipo especificado
     * @param type tipo de clase especificado
     * @return la clase que construye el objeto deseado y especificado por el tipo
     */
    std::unique_ptr<GameObjects> getFactory(std::string type);
}
#endif	/* FACTORYGAMEOBJECTS_H */

