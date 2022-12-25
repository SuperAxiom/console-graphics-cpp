/*
 * Point3d.h
 *
 *  Created on: Dec 23, 2022
 *      Author: vladyslav
 */

#ifndef CONSOLE_GRAPHICS_CPP_POINT3D_H_
#define CONSOLE_GRAPHICS_CPP_POINT3D_H_

#include "Matrix.hpp"

class Point3d {
	Matrix coordinates;
public:
	// Constructor;
	Point3d(float x, float y, float z);

	// Getters
	float getX() const;
	float getY() const;
	float getZ() const;
};

#endif /* CONSOLE_GRAPHICS_CPP_POINT3D_H_ */
