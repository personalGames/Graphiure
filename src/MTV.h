/* 
 * File:   MTV.h
 * Author: dorian
 * https://github.com/simplerr/Project-Mayhem/tree/178acb0ff06d60c99b1891e4e40644ce8a056764
 *
 * Created on 23 de abril de 2015, 13:19
 */

#ifndef MTV_H
#define	MTV_H

#include "Vector.h"

class MTV
{
public:
	MTV(){
		pushX = pushY = 0;
		normal = Vector(0, 0);
	};

	MTV(double d, Vector axis)	{
		pushX = d*axis.x;
		pushY = d*axis.y;
		normal = axis;
	};

	void inverse()	{
		pushX *= -1;
		pushY *= -1;
		normal.x *= -1;
		normal.y *= -1;
	}

	bool   collision;
	double pushX;
	double pushY;
	Vector  normal;
};

#endif	/* MTV_H */

