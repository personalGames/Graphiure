/* 
 * File:   ConvexHull.h
 * Author: dorian
 *
 * Created on 21 de marzo de 2015, 13:53
 */

#ifndef CONVEXHULL_H
#define	CONVEXHULL_H

// Implementation of Andrew's monotone chain 2D convex hull algorithm.
// Asymptotic complexity: O(n log n).
// Practical performance: 0.5-1.0 seconds for n=1000000 on a 1GHz machine.
#include <algorithm>
#include <vector>

//typedef double coord_t; // coordinate type
//typedef double coord2_t; // must be big enough to hold 2*max(|coordinate|)^2

struct Point {
    double x, y;
    Point():x(),y(){};
    Point(double x, double y):x(x),y(y){};

    bool operator<(const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.

double crossPoint(const Point &O, const Point &A, const Point &B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.

std::vector<Point> convertConvexHull(std::vector<Point> P) {
    int n = P.size(), k = 0;
    std::vector<Point> H(2 * n);

    // Sort points lexicographically
    std::sort(P.begin(), P.end());

    // Build lower hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && crossPoint(H[k - 2], H[k - 1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }

    // Build upper hull
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && crossPoint(H[k - 2], H[k - 1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }

    H.resize(k);
    return H;
}

#endif	/* CONVEXHULL_H */

