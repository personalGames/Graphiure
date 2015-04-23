/* 
 * File:   Triangle.h
 * Author: dorian
 *
 * Created on 6 de abril de 2015, 12:55
 */

#ifndef TRIANGLE_H
#define	TRIANGLE_H

#include "Utilities.h"


struct Triangle {

    Triangle(sf::Vector2f& p0, sf::Vector2f& p1, sf::Vector2f& p2) : p0(p0), p1(p1), p2(p2) {
    }
    
    Triangle() : p0(), p1(), p2() {
    }

    bool pointInside(sf::Vector2f& point) {
        float Area = 1 / 2 * (-p1.y * p2.x + p0.y * (-p1.x + p2.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y);
        float s = 1 / (2 * Area)*(p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * point.x + (p0.x - p2.x) * point.y);
        float t = 1 / (2 * Area)*(p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * point.x + (p1.x - p0.x) * point.y);

        return s > 0 && t > 0 && 1 - s - t > 0;
    }
    
    sf::FloatRect getBounds(){
        sf::VertexArray array=sf::VertexArray();
        array.append(sf::Vertex(p0));
        array.append(sf::Vertex(p1));
        array.append(sf::Vertex(p2));
        
        return array.getBounds();
    }

    bool aabbCollision(sf::FloatRect& oneRect) {
        bool result = false;
        result = result | oneRect.contains(p0);
        result = result | oneRect.contains(p1);
        result = result | oneRect.contains(p2);

        if (!result) {
            sf::Vector2f point = sf::Vector2f(oneRect.left, oneRect.top);
            result = result | pointInside(point);
            point = sf::Vector2f(oneRect.left + oneRect.width, oneRect.top);
            result = result | pointInside(point);
            point = sf::Vector2f(oneRect.left, oneRect.top + oneRect.height);
            result = result | pointInside(point);
            point = sf::Vector2f(oneRect.left + oneRect.width, oneRect.top + oneRect.height);
            result = result | pointInside(point);
        }
        return result;
    }
    
    bool triangleVSTriangle(Triangle& triangle){
        if(pointInside(triangle.p0) | pointInside(triangle.p1) | pointInside(triangle.p2)){
            return true;
        }
        bool result=false;
        
        result=result | LineCollision(p0,p1, triangle.p0, triangle.p1);
        result=result | LineCollision(p0,p1, triangle.p1, triangle.p2);
        result=result | LineCollision(p0,p1, triangle.p2, triangle.p0);
        
        if(result){
            return result;
        }
        
        result=result | LineCollision(p1,p2, triangle.p0, triangle.p1);
        result=result | LineCollision(p1,p2, triangle.p1, triangle.p2);
        result=result | LineCollision(p1,p2, triangle.p2, triangle.p0);
        
        if(result){
            return result;
        }
        
        result=result | LineCollision(p2,p0, triangle.p0, triangle.p1);
        result=result | LineCollision(p2,p0, triangle.p1, triangle.p2);
        result=result | LineCollision(p2,p0, triangle.p2, triangle.p0);
        
        return result;
        
    }

    sf::Vector2f p0, p1, p2;
};


#endif	/* TRIANGLE_H */

