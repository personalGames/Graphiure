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

namespace FactoryGameObjects{
    std::unique_ptr<GameObjects> getFactory(std::string type);
}
#endif	/* FACTORYGAMEOBJECTS_H */

