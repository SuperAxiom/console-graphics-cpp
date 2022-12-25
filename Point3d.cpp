/*
 * Point3d.cpp
 *
 *  Created on: Dec 23, 2022
 *      Author: vladyslav
 */

#include "Point3d.hpp"

// Constructor;
Point3d::Point3d(float x, float y, float z){
	float values[3] = {x, y, z};
	this->coordinates = Matrix(values, 3);
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

