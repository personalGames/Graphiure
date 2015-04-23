/* 
 * File:   StaticBlock.cpp
 * Author: dorian
 * 
 * Created on 28 de marzo de 2015, 23:44
 */

#include "StaticBlock.h"
#include "Entity.h"
#include "Behaviour.h"
#include "Position.h"

Entity* StaticBlock::prepareEntity(PropertyManager& parameters) {
    Entity* entity = new Entity();

    Collision* colli = new Collision();
    sf::Vector2f pos = parameters.Get<sf::Vector2f>("Position");
    Position* position = new Position();
    position->updatePosition(pos.x, pos.y);

    sf::Transformable transform = position->getPosition();
    colli->update(transform);
    colli->setArrayVertex(parameters.Get<sf::VertexArray*>("Vertex"));
    colli->applyRatio(parameters.Get<sf::Vector2f>("Ratio"));
    colli->setType(TypeCollision::STATIC);

    position->setPosition(colli->getTransform());

    entity->Add<Position*>("Position", position);
    entity->Add<Collision*>("Collision", colli);

    entity->Add<Collision*>("Debug", colli);

    Behaviour* behaviour = new Behaviour();
    makeBehaviour(entity->getId(), behaviour);
    entity->Add<Behaviour*>("Behaviour", behaviour);

    return entity;
}

void StaticBlock::makeBehaviour(IdEntity idObject, Behaviour* behaviour) {
    auto aFunction = [idObject] (MessageCollision * message) {
        std::cout<<"Touch"<<std::endl;
        sf::FloatRect staticRect;
        sf::FloatRect moveRect;
        
        Entity* staticEntity=message->entityOne;
        Entity* moveEntity=message->entityTwo;
        
        double x,y;
        x=message->mtv.pushX;
        y=message->mtv.pushY;
        moveEntity->Get<Position*>("Position")->updatePosition(x,y);
        
        std::cout<<x<<" "<<y<<std::endl;
        
//        Triangle tri;
//        if(staticEntity->getId()==idObject){
//            staticRect=message->oneTriangle.getBounds();
//            tri=message->oneTriangle;
//            
//        }else{
//            moveEntity=staticEntity;
//            staticEntity=message->entityTwo;
//            staticRect=message->twoTriangle.getBounds();
//            tri=message->twoTriangle;
//        }
//        moveRect=moveEntity->Get<Collision*>("Collision")->getAABB();
//        
//        float x=0;
//        float y=0;
//        sf::FloatRect intersection=sf::FloatRect();
//        staticRect.intersects(moveRect,intersection);
//        if(message->axisX){
//            if(message->toRightDown){
//                //personaje entra por la parte izquierda
//                std::cout<<"Choco por el izquierdo del lago"<<std::endl;
//                float right=std::min(tri.p0.x, std::min( tri.p1.x, tri.p2.x));
//                x=right-moveRect.width*2;
//            }else{
//                std::cout<<"Choco por el derecho del lago"<<std::endl;
//                float left=std::max(tri.p0.x, std::max( tri.p1.x, tri.p2.x));
//                x=left-moveRect.width;
//            }
//            
//            y=moveEntity->Get<Position*>("Position")->getPosition().getPosition().y;
//        }else{
//            
//            if(message->toRightDown){
//                //choca por arriba
//                std::cout<<"Choco por el superior del lago"<<std::endl;
//                float up=std::min(tri.p0.y, std::min(tri.p1.y, tri.p2.y));
//                y=up-moveRect.height*3;
//            }else{
//                std::cout<<"Choco por el inferior del lago"<<std::endl;
//                float up=std::max(tri.p0.y, std::max(tri.p1.y, tri.p2.y));
//                y=up-moveRect.height;
//            }
//            
//            x=moveEntity->Get<Position*>("Position")->getPosition().getPosition().x;
//        }
//        
//        moveEntity->Get<Position*>("Position")->setPosition(x,y);
    };
    //guardo la función creada
    behaviour->behaviourFunction = aFunction;
}

//void StaticBlock::makeBehaviour(IdEntity idObject, Behaviour* behaviour) {
//    auto aFunction = [idObject] (MessageCollision * message) {
//        Entity* other = message->entityOne;
//        Entity* me = message->entityTwo;
//
//        //        float distance = 0;
//        //        sf::FloatRect oneRect = message->oneTriangle.getBounds();
//        //        sf::FloatRect twoRect = message->twoTriangle.getBounds();
//        //        int sign=1; //supongamos que a quien modifico es oneRect
//        //        if (message->axisX) {
//        //            if (oneRect.left > twoRect.left) {
//        //                //oneRect queda a la derecha, para corregir sería positivo
//        //                distance = oneRect.left - twoRect.left + twoRect.width;
//        //                
//        //            } else {
//        //                sign=-1;
//        //                distance = twoRect.left -(oneRect.width + oneRect.left);
//        //            }
//        //
//        //        } else {
//        //            if (oneRect.top > twoRect.top) {
//        //                
//        //                distance = oneRect.top - twoRect.top + twoRect.height;
//        //            } else {
//        //                sign=-1;
//        //                distance = twoRect.top -(oneRect.top + oneRect.height);
//        //            }
//        //        }
//        //
//        //
//        //
//        //        Entity* modify = message->entityOne;
//        //        if (modify->getId() == idObject) {
//        //            //oneRect venía a ser de entity one, si cambio de entity, también
//        //            //cambio el valor del signo
//        //            sign=-1*sign;
//        //            modify = message->entityTwo;
//        //        }
//        //
//        //
//        //
//        //        sf::Vector2f separation = sf::Vector2f(0, 0);
//        //        if (message->axisX) {
//        //            separation.x = sign*distance;
//        //        } else {
//        //            separation.y = sign*distance;
//        //        }
//        //
//        //        Position* position = modify->Get<Position*>("Position");
//        //        position->updatePosition(separation.x, separation.y);
//        //        position->updatePosition(0, 0);
//
//        bool changed = false;
//        if (other->getId() == idObject) {
//            me = other;
//            changed = true;
//            other = message->entityTwo;
//        }
//
//        Collision* collisionTwo = other->Get<Collision*>("Collision");
//
//        if (collisionTwo->getType() == TypeCollision::STATIC) {
//            return;
//        }
//
//        sf::FloatRect bound = collisionTwo->getAABB();
//        sf::FloatRect collision = (changed) ? message->twoTriangle.getBounds() : message->oneTriangle.getBounds();
//        Position* positionTwo = other->Get<Position*>("Position");
//        float x = 0;
//        float y = 0;
//        sf::FloatRect intersection = sf::FloatRect();
//        bound.intersects(collision, intersection);
//        if (message->axisX) {
//            //collision at right
//            if (intersection.contains(bound.left + bound.width - 0.1, bound.top + 0.1)
//                    || intersection.contains(bound.left + bound.width - 0.1,
//                    bound.top + bound.height + 0.1)) {
//                x = -(intersection.width + 0.5);
//
//                //collision at left
//            } else {
//                x = intersection.width + 0.5;
//            }
//            
//            
//        } else {
//            //collision at top
//            if (intersection.contains(bound.left, bound.top)
//                    || intersection.contains(bound.left + bound.width, bound.top)) {
//                y = intersection.height + 0.5;
//
//                //collision at bottom
//            } else {
//                y = -(intersection.height + 0.5);
//            }
//        }
//
//        positionTwo->updatePosition(x, y);
//        positionTwo->updatePosition(0, 0);
//    };
//
//    //guardo la función creada
//    behaviour->behaviourFunction = aFunction;
//}
