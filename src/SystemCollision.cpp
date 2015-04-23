/* 
 * File:   SystemCollision.cpp
 * Author: dorian
 * 
 * Created on 15 de marzo de 2015, 21:47
 */

#include "SystemCollision.h"
#include <limits>
#include <cmath>
#include <iostream>

SystemCollision::SystemCollision(sf::FloatRect bounds) : ISystem(), tree() {
    type = TypeSystem::COLLISION;
    tree = new QuadTree(0, bounds);
}

SystemCollision::SystemCollision() : ISystem(), tree() {
    type = TypeSystem::COLLISION;
    tree = new QuadTree(0);
}

SystemCollision::~SystemCollision() {
}

void SystemCollision::registerEntity(Entity* entity) {
    if (entity->HasID("Collision") && entity->HasID("Position")) {
        tree->insert(entity);
    }
}

void SystemCollision::removedEntity(Entity* entity) {
    tree->remove(entity);
}

void SystemCollision::checkCollisions(sf::FloatRect region) {
    QuadTree* subtree = tree->getNodeRegion(region);
    if (subtree == nullptr) {
        subtree = tree;
    }
    std::vector<Entity*> list = std::vector<Entity*>();

    //pillo la lista de posibles objetos de la escena
    subtree->getObjects(list);
    //itero los objetos
    for (std::vector<Entity*>::iterator it = list.begin(); it != list.end(); ++it) {
        Entity* entity = *(it);
        std::vector<Entity*> posibles = std::vector<Entity*>();
        //pillo la lista de objetos que pueden chocar con este entity
        subtree->retrieve(&posibles, entity);


        for (std::vector<Entity*>::iterator it = posibles.begin(); it != posibles.end(); ++it) {
            //llamar a collision detection y pasarle el mensaje que rellenará si resulta cierto
            MessageCollision* message = collisionDetection(entity, *(it));
            if (message != nullptr) {
                queue.push(message);
            }
        }
    }
}

MessageCollision* SystemCollision::collisionDetection(Entity* one, Entity* two) {
    //si son el mismo, fuera
    if (one->getId() == two->getId()) {
        return nullptr;
    }

    Collision* first = one->Get<Collision*>("Collision");
    Collision* second = two->Get<Collision*>("Collision");

    sf::FloatRect oneRect = first->getAABBSwept();
    sf::FloatRect anotherRect = second->getAABBSwept();

    MessageCollision* collide = nullptr;

    //collision with swept (CCD) check the first moment collide
    if (oneRect.intersects(anotherRect)) {
        collide = firstTimeCollision(one, two);
    }

    return collide;
}

MessageCollision* SystemCollision::firstTimeCollision(Entity* one, Entity* two) {
    //get the collisions
    Collision* firstCollision = one->Get<Collision*>("Collision");
    Collision* secondCollision = two->Get<Collision*>("Collision");

    //if both static, get out
    if (firstCollision->getType() == TypeCollision::STATIC && secondCollision->getType() == TypeCollision::STATIC) {
        //los dos son estáticos, lo ignoro no puede darse
        return nullptr;
    }
    //keep track of changed position of entities
    bool changed = false;

    //collision with swept (CCD) check the first moment collide
    sf::FloatRect firstRect;
    sf::FloatRect secondRect;
    sf::Vector2f velocity; //velocity of the dynamic body (second)


    //voy a establecer que el primero sea estático y el segundo dinámico
    //si los dos dinámicos, decido por velocidad
    if (firstCollision->getType() == TypeCollision::DYNAMIC && secondCollision->getType() == TypeCollision::DYNAMIC) {
        //ambos dinámicos, consideraré como estático el que menor velocidad tenga
        Velocity* velOne = one->Get<Velocity*>("Velocity");
        Velocity* velTwo = two->Get<Velocity*>("Velocity");
        if (velOne > velTwo) {
            //cambio, que el dinámico irá en segundo lugar. La velocidad el del más rapido
            changed = true;
            secondRect = firstCollision->getAABB();
            firstRect = secondCollision->getAABB();
            velocity = velOne->getVelocity();
        } else {
            secondRect = secondCollision->getAABB();
            firstRect = firstCollision->getAABB();
            velocity = velTwo->getVelocity();
        }

    } else if (secondCollision->getType() == TypeCollision::DYNAMIC) {
        //el primero es estático y el segundo dinámico
        firstRect = firstCollision->getAABB();
        secondRect = secondCollision->getAABB();
        velocity = two->Get<Velocity*>("Velocity")->getVelocity();

    } else if (firstCollision->getType() == TypeCollision::DYNAMIC) {
        //el primero es el dinámico, intercambio las posiciones
        changed = true;
        secondRect = firstCollision->getAABB();
        firstRect = secondCollision->getAABB();
        velocity = one->Get<Velocity*>("Velocity")->getVelocity();
    }


    //el primero es el estático, el segundo se mueve y es el que se desplazará
    //if collide, get the first and final time of collision
    //get the fastest entity
    float timeXCollision = 0;
    float timeYCollision = 0;

    float xMove, yMove, xStatic, yStatic, xMoveFinal, yMoveFinal, xStaticFinal, yStaticFinal;

    //presupongo una colision inicial (choca el que se mueve con la parte inferior derecha del static)
    xMove = secondRect.left;
    yMove = secondRect.top;
    xMoveFinal = secondRect.left + secondRect.width;
    yMoveFinal = secondRect.top + secondRect.width;

    xStatic = firstRect.left + firstRect.width;
    yStatic = firstRect.top + firstRect.height;
    xStaticFinal = firstRect.left;
    yStaticFinal = firstRect.top;

    //compruebo con la velocidad si me he equivocado en mi suposición y corrigo los valores asignados
    bool negative = false;
    if (velocity.x != 0) {
        if (velocity.x < 0) {
            negative = true;
        }
        xMove = secondRect.left + secondRect.width;
        xStatic = firstRect.left;
        xMoveFinal = secondRect.left;
        xStaticFinal = firstRect.left + firstRect.width;
    }
    if (velocity.y != 0) {
        if (velocity.y < 0) {
            negative = true;
        }
        yMove = secondRect.top + secondRect.width;
        yStatic = firstRect.top;
        yMoveFinal = secondRect.top;
        yStaticFinal = firstRect.top + firstRect.height;
    }

    //calculo el momento de colisión
    timeXCollision = (xMove - xStatic) / velocity.x;
    timeYCollision = (yMove - yStatic) / velocity.y;

    bool x = true;
    float time = 0;
    if (std::isfinite(timeXCollision)) {
        float timeCollision2 = (xMoveFinal - xStaticFinal) / -velocity.x;
        time = timeCollision2 - timeXCollision;
    } else {
        float timeCollision2 = (yMoveFinal - yStaticFinal) / -velocity.y;
        time = timeCollision2 - timeYCollision;
        x = false;
    }

    //tengo el tiempo y el eje, con ello puedo conocer las posiciones de cuando chocaron
    //triangulo las figuras y compruebo exactamente cómo han chocado
    MessageCollision* collision = triangulate(firstCollision, secondCollision, time);
    if (collision != nullptr) {
        //me aseguro que la entidad corresponde con el triángulo colisionado
        //(que el triangulo es de su figura, no del otro)
        if (changed) {
            collision->entityOne = two;
            collision->entityTwo = one;
        } else {
            collision->entityOne = one;
            collision->entityTwo = two;
        }

        collision->axisX = x;
        collision->toRightDown = !negative;

    }

    return collision;
}

MessageCollision* SystemCollision::triangulate(Collision* first, Collision* second, float time) {
    std::vector<Triangle> triangles;
    std::vector<Triangle> trianglesCollision;
    std::vector<Triangle> trianglesSecond;
    std::vector<sf::Vector2f> extra = std::vector<sf::Vector2f>();

    std::vector<Triangle> collisionOne, collisionTwo;

    //recojo las colisiones
    Collision* one = first;
    Collision* two = second; //menos vertices
    sf::FloatRect oneRect;

    //me aseguro que en el segundo esta el que tiene menos vértices
    bool flipped = false;
    if (first->vertices->getVertexCount() < second->vertices->getVertexCount()) {
        one = second;
        two = first;
        oneRect = one->getAABB(time);
        flipped = true;
    }

    oneRect = one->getAABB(time);
    if ((time <= 0) | (oneRect.left < 0) | (oneRect.top < 0)) {
        oneRect = one->getAABB();
    }
    //triangulizo el de menos vértices
    sf::Transform transform2 = two->getTransform().getTransform();
    CreateDelaunayTriangulation(two->vertices, two->vertices->getVertexCount(), extra, 0, triangles, transform2);
    //saco los triangulos que colisionan
    for (uint i = 0; i < triangles.size(); ++i) {
        bool result = triangles[i].aabbCollision(oneRect);
        if (result) {
            trianglesCollision.push_back(triangles[i]);
        }
    }

    bool collisionTriangles = false;
    //si hay triángulos que colisionan, triangulizo el segundo
    if (trianglesCollision.size() > 0) {
        sf::Transform transform = one->getTransform().getTransform();
        CreateDelaunayTriangulation(one->vertices, one->vertices->getVertexCount(), extra, 0, trianglesSecond, transform);
        //por cada triangulizado, comparo con los triangulos que colisionaban antes
        bool result = false;
        for (uint i = 0; i < trianglesSecond.size(); ++i) {
            for (uint j = 0; j < trianglesCollision.size() && !result; ++j) {
                result = trianglesSecond[i].triangleVSTriangle(trianglesCollision[j]);
                if (result) {
                    collisionOne.push_back(trianglesCollision[j]);
                    collisionTwo.push_back(trianglesSecond[i]);
                    collisionTriangles = true;
                }
            }
        }
    }

    //devuelvo el mtv por si lo van a usar
    //calculo mtv...
    //sumo al mtv  el plus por la posición final dado por el movimiento desde el momento que chocó

    MessageCollision* message = nullptr;
    //guardo los triangulos en el mensaje de collisión
    if (collisionTriangles) {
        message = new MessageCollision();
        message->mtv=checkCollisions(collisionTwo[0],collisionOne[0]);
        //        if (flipped) {
        //            message->oneTriangle = collisionTwo;
        //            message->twoTriangle = collisionOne;
        //        } else {
        //            message->oneTriangle = collisionOne;
        //            message->twoTriangle = collisionTwo;
        //        }
    }
    return message;
}

MTV SystemCollision::checkCollisions(Triangle& poly1, Triangle& poly2) {
    MTV mtv;
    mtv.collision = false;

    sf::FloatRect Rect1 = poly1.getBounds();
    sf::FloatRect Rect2 = poly2.getBounds();

    if (Rect1.left > (Rect2.left + Rect2.width) || (Rect1.left + Rect1.width) < Rect2.left
            || Rect1.top + Rect1.height < Rect2.top || Rect1.top > (Rect2.top + Rect2.height)) {
        return mtv;
    }
    //    else if (!detailed) {
    //        mtv.collision = true;
    //        return mtv;
    //    }

//    Triangle tmp1 = poly1;
//    Triangle tmp2 = poly2;

    Vector axis; // Axis we will project onto
    Vector projection; // The direction of the projection
    int i; // Current i 
    double minA, maxA, minB, maxB, axisLen, tmp, minLen = 999999, tmpDepth = 1;


    for (int i = 0; i < 3; i++) {
        if (i == 0) {
            axis.x = -(poly1.p2.y - poly1.p0.y);
            axis.y = poly1.p2.x - poly1.p0.x;
        } else if (i == 1) {
            axis.x = -(poly1.p0.y - poly1.p1.y);
            axis.y = poly1.p0.x - poly1.p1.x;
        } else {
            axis.x = -(poly1.p1.y - poly1.p2.y);
            axis.y = poly1.p1.x - poly1.p2.x;
        }
        axisLen = sqrt(axis.x * axis.x + axis.y * axis.y);
        axis.x /= axisLen;
        axis.y /= axisLen;

        minA = maxA = (poly1.p0.x * axis.x + poly1.p0.y * axis.y);

        for (int i = 1; i < 3; i++) {
            switch (i) {
                case 0:
                    tmp = (poly1.p0.x * axis.x + poly1.p0.y * axis.y);
                    break;
                case 1:
                    tmp = (poly1.p1.x * axis.x + poly1.p1.y * axis.y);
                    break;
                case 2:
                    tmp = (poly1.p2.x * axis.x + poly1.p2.y * axis.y);
                    break;
            }
            

            if (tmp < minA)
                minA = tmp;
            else if (tmp > maxA)
                maxA = tmp;
        }

        /* correct with offset */ //already corrected
//        tmp = poly1.getPos().x * axis.x + poly1.getPos().y * axis.y;
//        minA += tmp;
//        maxA += tmp;

        /* project Shape B's points on the axis to find MIN and MAX points */
        minB = maxB = (poly2.p0.x * axis.x + poly2.p0.y * axis.y);

        for (int i = 1; i < 3; i++) {
            switch (i) {
                case 0:
                    tmp = (poly2.p0.x * axis.x + poly2.p0.y * axis.y);
                    break;
                case 1:
                    tmp = (poly2.p1.x * axis.x + poly2.p1.y * axis.y);
                    break;
                case 2:
                    tmp = (poly2.p2.x * axis.x + poly2.p2.y * axis.y);
                    break;
            }

            if (tmp < minB)
                minB = tmp;
            else if (tmp > maxB)
                maxB = tmp;
        }

        /* correct with offset */
//        tmp = poly2.getPos().x * axis.x + poly2.getPos().y * axis.y;
//        minB += tmp;
//        maxB += tmp;

        /* test if they intersect, if not then store the penetration depth and axis */
        if (minA > maxB || maxA < minB) {
            mtv.collision = false;
            return mtv;
        } else {
            // the projection axis is to be used by the player (objectB)
            if (maxA < maxB) {
                tmpDepth = maxA - minB;
                if (tmpDepth < minLen) {
                    minLen = tmpDepth;
                    projection = axis;
                }
            } else if (maxA > maxB) {
                tmpDepth = maxB - minA;
                if (tmpDepth < minLen) {
                    minLen = tmpDepth;
                    projection.x = axis.x*-1; // WHY? - to correct for ShapeB
                    projection.y = axis.y*-1;
                }
            }
        }
    }

    /* the same thing again but now for object B, sometimes a collision from Shape A isn't a collision for Shape B */
    /*
            - see above for detailed comments
     */

//    // test Shape B's sides
//    for (i = 0; i < 3; i++) {
//        /* get the axis we will project on */
//        if (i == 0) {
//            axis.x = (poly2.p2.y - poly2.p0.y);
//            axis.y = poly2.p2.x - poly2.p0.x;
//        } else if (i == 1) {
//            axis.x = (poly2.p0.y - poly2.p1.y);
//            axis.y = poly2.p0.x - poly2.p1.x;// should be reversed?:O
//        } else {
//            axis.x = (poly2.p1.y - poly2.p2.y);
//            axis.y = poly2.p1.x - poly2.p2.x;// should be reversed?:O
//        }
//
//        /* normalize the axis */
//        axisLen = sqrt(axis.x * axis.x + axis.y * axis.y);
//        axis.x /= axisLen;
//        axis.y /= axisLen;
//
//        /* project Shape B's points on the axis to find MIN and MAX points */
//        minB = maxB = (poly2.p0.x * axis.x + poly2.p0.y * axis.y);
//        
//        for (int i = 1; i < 3; i++) {
//            switch (i) {
//                case 0:
//                    tmp = (poly2.p0.x * axis.x + poly2.p0.y * axis.y);
//                    break;
//                case 1:
//                    tmp = (poly2.p1.x * axis.x + poly2.p1.y * axis.y);
//                    break;
//                case 2:
//                    tmp = (poly2.p2.x * axis.x + poly2.p2.y * axis.y);
//                    break;
//            }
//
//            if (tmp < minB)
//                minB = tmp;
//            else if (tmp > maxB)
//                maxB = tmp;
//        }
//
//        /* correct with offset */
////        tmp = poly2.getPos().x * axis.x + poly2.getPos().y * axis.y;
////        minB += tmp;
////        maxB += tmp;
//
//        /* project Shape A's points on the axis to find MIN and MAX points */
//        minA = maxA = (poly1.p0.x * axis.x + poly1.p0.y * axis.y);
//
//        for (int i = 1; i < 3; i++) {
//            switch (i) {
//                case 0:
//                    tmp = (poly1.p0.x * axis.x + poly1.p0.y * axis.y);// - gets removed??
//                    break;
//                case 1:
//                    tmp = (poly1.p1.x * axis.x + poly1.p1.y * axis.y);// - gets removed??
//                    break;
//                case 2:
//                    tmp = (poly1.p2.x * axis.x + poly1.p2.y * axis.y);// - gets removed??
//                    break;
//            }
//            
//
//            if (tmp < minA)
//                minA = tmp;
//            else if (tmp > maxA)
//                maxA = tmp;
//        }
//
//        /* correct with offset */
////        tmp = poly1.getPos().x * axis.x + poly1.getPos().y * axis.y;
////        minA += tmp;
////        maxA += tmp;
//
//        /* test if they intersect, if not then return false */
//        if (minA > maxB) {// || maxA < minB)	{
//            mtv.collision = false;
//            return mtv;
//        } else {
//            // get the minimal depth of intersection and the correct axis
//            if (maxA < maxB) // Will have to make it work with triangles as well!
//                tmpDepth = maxA - minB;
//            //else if(maxA > maxB)	// HAAAX KINGGG!!!"!!!b<3333
//            //	tmpDepth = maxB - minA;
//
//            if (tmpDepth < minLen) {
//
//                minLen = tmpDepth;
//                projection = axis;
//            }
//        }
//    }
    /* return minimum intersection depth */
    mtv = MTV(minLen, projection);
    mtv.collision = true;
    return mtv;
}

void SystemCollision::update(sf::Time dt) {
    tree->update();
}

void SystemCollision::updateSecondPart(sf::Time dt) {
    tree->update();
}

void SystemCollision::newWorldCollision(sf::FloatRect bounds) {
    tree->clear();
    delete tree;
    tree = new QuadTree(0, bounds);
}

void SystemCollision::clear() {
    tree->clear();
}

void SystemCollision::finalize() {
    tree->clear();
}

void SystemCollision::correctInsidePosition(Entity* entity) {
    Collision* collision = entity->Get<Collision*>("Collision");
    sf::FloatRect viewBounds = tree->getBounds();

    sf::Vector2f position = entity->Get<Position*>("Position")->getPosition().getPosition();
    sf::FloatRect bounds = collision->getAABB();
    position.x = std::max(position.x, viewBounds.left);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - bounds.width);
    position.y = std::max(position.y, viewBounds.top);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - bounds.height);
    Position* pos = entity->Get<Position*>("Position");

    sf::Transformable newPosition = sf::Transformable();
    newPosition.setPosition(position.x, position.y);
    pos->setPosition(newPosition);
}

void SystemCollision::resolveCollisions() {
    while (queue.size() > 0) {
        MessageCollision* collision = queue.front();
        queue.pop();

        //lo resolverá el entity
        if (collision->entityOne->HasID("Behaviour")) {
            collision->entityOne->Get<Behaviour*>("Behaviour")->behaviourFunction(collision);
        }

        delete collision;

    }
}
