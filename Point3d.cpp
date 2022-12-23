/*
 * Point3d.cpp
 *
 *  Created on: Dec 23, 2022
 *      Author: vladyslav
 */

#include "Point3d.h"

// Constructor;
Point3d::Point3d(float x, float y, float z){
	float** matr;

	matr = new float*[3];
	for (uint i = 0; i < 3; i++)
		*(matr + i) = new float;

	*(*(matr + 0) + 0) = x;
	*(*(matr + 1) + 0) = y;
	*(*(matr + 2) + 0) = z;


	this->coordinates = Matrix(matr, 3, 1);
}

// Getters
float Point3d::getX() const{
	return this->coordinates.getValue(0, 0);
}

float Point3d::getY() const{
	return this->coordinates.getValue(1, 0);
}

float Point3d::getZ() const{
	return this->coordinates.getValue(2, 0);
}

