/**
 * Por el usuario dc443 en http://www.box2d.org/forum/viewtopic.php?f=4&t=83&start=100
 * Según la página de descarga, Steven Lu http://sourceforge.net/projects/box2dsandbox/
 */

#include <iostream>
#include <stdlib.h> // for C qsort 
#include <cmath>
#include <time.h> // for random
#include <vector>
#include <SFML/Graphics.hpp>
#include "Triangle.h"

const double EPSILON = 0.000001;

struct ITRIANGLE{
	int p1, p2, p3;
};

struct IEDGE{
	int p1, p2;
};

struct XYZ{
	double x, y;
};


int XYZCompare(const void *v1, const void *v2);

int CircumCircle(double xp, double yp, double x1, double y1, double x2, 
				 double y2, double x3, double y3, double &xc, double &yc, double &r);

int Triangulate(int nv, XYZ pxyz[], ITRIANGLE v[], int &ntri);

int CreateDelaunayTriangulation(sf::VertexArray* verts, int n_verts, 
                    std::vector<sf::Vector2f> & extraPoints, int pointCount, 
                    std::vector<Triangle> & triangles, sf::Transform& transform);