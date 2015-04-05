/* 
 * File:   ConvexTest.h
 * Author: dorian
 *
 * Created on 5 de abril de 2015, 17:15
 */

#ifndef CONVEXTEST_H
#define	CONVEXTEST_H

#include "StructCollision.h"

float crossProductLength(float Ax, float Ay,
        float Bx, float By, float Cx, float Cy) {
    // Get the vectors' coordinates.
    float BAx = Ax - Bx;
    float BAy = Ay - By;
    float BCx = Cx - Bx;
    float BCy = Cy - By;

    // Calculate the Z coordinate of the cross product.
    return (BAx * BCy - BAy * BCx);
}

bool polygonIsConvex(StructCollision* collision) {
    // Return True if the polygon is convex.

    // For each set of three adjacent points A, B, C,
    // find the cross product AB · BC. If the sign of
    // all the cross products is the same, the angles
    // are all positive or negative (depending on the
    // order in which we visit them) so the polygon
    // is convex.
    bool got_negative = false;
    bool got_positive = false;
    sf::VertexArray points=*(collision->vertices);
    int num_points = points.getVertexCount();;
    int B, C;
    for (int A = 0; A < num_points; A++) {
        B = (A + 1) % num_points;
        C = (B + 1) % num_points;
        float cross_product =
                crossProductLength(
                points[A].position.x, points[A].position.y,
                points[B].position.x, points[B].position.y,
                points[C].position.x, points[C].position.y);
        if (cross_product < 0) {
            got_negative = true;
        } else if (cross_product > 0) {
            got_positive = true;
        }
        if (got_negative && got_positive) return false;
    }

    // If we got this far, the polygon is convex.
    return true;
}




#endif	/* CONVEXTEST_H */

