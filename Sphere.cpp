#include "Sphere.hpp"

// Constructors
Sphere::Sphere(Point3d center, float radius){
    this->center = center;
    this->radius = radius;
}

// Getters
Point3d Sphere::getCenter() const{
    return this->center;
}

float Sphere::getRadius() const{
    return this->radius;
}

// Interactions
bool Sphere::isBelong(const Point3d& point){
    float x = point.getX();
    float y = point.getY();
    float z = point.getZ();

    float x0 = this->center.getX();
    float y0 = this->center.getY();
    float z0 = this->center.getZ();
    float r = this->radius;

    float lhs = 0.0;
    lhs += (x - x0) * (x - x0);
    lhs += (y - y0) * (y - y0);
    lhs += (z - z0) * (z - z0);

    float rhs = r*r;

    if (lhs == rhs)
        return true;
    return false;
}

bool Sphere::isIntersect(const Line3d& line){
    // Init vars
	// Line's params
	float p1 = line.getDirection().getX();
	float p2 = line.getDirection().getY();
	float p3 = line.getDirection().getZ();
	float x0 = line.getPoint().getX();
	float y0 = line.getPoint().getY();
	float z0 = line.getPoint().getZ();

	// Sphere's params
	float x01 = this->center.getX();
	float y01 = this->center.getY();
	float z01 = this->center.getZ();
	float r = this->radius;

	// Find params for discriminant
	float a = (p1 * p1) + (p2 * p2) + (p3 * p3);
	float b = 2 * (p1 * (x0 - x01) + p2 * (y0 -y01) + p3 * (z0 -z01));
	float c = (x0 -x01) * (x0 - x01);
	c += (y0 - y01) * (y0 - y01);
	c += (z0 -z01) * (z0 - z01);
	c -= r * r;

	// Find discriminant
	float d = b * b - 4 * a * c;

	// If there is real solution then they are intersected
	if (d < 0)
		return false;
	return true;
}