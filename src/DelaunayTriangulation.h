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

/**
 * Estructuras para la triangulación
 */
struct ITRIANGLE{
	int p1, p2, p3;
};

struct IEDGE{
	int p1, p2;
};

struct XYZ{
	double x, y;
};


/**
 * Compara dos puntos
 * @param v1
 * @param v2
 * @return 
 */
int XYZCompare(const void *v1, const void *v2);

/**
 * 
 * @param xp
 * @param yp
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param x3
 * @param y3
 * @param xc
 * @param yc
 * @param r
 * @return 
 */
int CircumCircle(double xp, double yp, double x1, double y1, double x2, 
				 double y2, double x3, double y3, double &xc, double &yc, double &r);

/**
 * Método auxiliar en la triangulización
 * @param nv
 * @param pxyz
 * @param v
 * @param ntri
 * @return 
 */
int Triangulate(int nv, XYZ pxyz[], ITRIANGLE v[], int &ntri);

/**
 * returns triangle count
 * Any invalid vectors are ignored (they are delimiters for multiple polygons)
 * @param verts vertices de la figura
 * @param n_verts número de vértices de la figura
 * @param extraPoints vértices extra de la figura
 * @param pointCount conteo de los vértices extra
 * @param triangles vector de triángulos resultantes, se rellena en el método
 * @param transform transformada de los vértices
 * @return número de triángulos
 */
int CreateDelaunayTriangulation(sf::VertexArray* verts, int n_verts, 
                    std::vector<sf::Vector2f> & extraPoints, int pointCount, 
                    std::vector<Triangle> & triangles, sf::Transform& transform);