#include "Plane.hpp"

// Constructors
Plane::Plane(float a, float b, float c, float d){
    if (a == 0.0 && b == 0.0 && c == 0.0)
        throw "InvalidVector";

    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d; 
}

// Getters
Matrix Plane::getParams() const{
    float values[4] = {this->a, this->b, this->c, this->d};
    return Matrix(values, 4);
}

Vector3d Plane::getNormVector() const{
    return Vector3d(this->a, this->b, this->c);
}

float Plane::getD() const{
    return this->d;
}

// Interactions
bool Plane::isBelong(const Point3d& point){
    float x = point.getX();
    float y = point.getY();
    float z = point.getZ();

    float lhs = this->a * x + this->b * y + this->c * z + this->d;

    if (lhs == 0)
        return true;
    return false;
}

bool Plane::isIntersect(const Line3d& line){
    Vector3d norm = this->getNormVector();
    Vector3d dir = line.getDirection();

    // If norm vector and dir vector are perpendicular then plane and line are parallel
    // Otherwise they are intersect 
    if (norm * dir == 0.0)
        return false;
    return true;
}

Point3d Plane::findIntersection(const Line3d& line){
    if (!this->isIntersect(line))
        throw "IntersectionError";
    
    float t_num = this->a * line.getPoint().getX();
	t_num += this->b * line.getPoint().getY();
	t_num += this->c * line.getPoint().getZ();
	t_num += this->d;

	float t_denum = this->a * line.getDirection().getX();
	t_denum += this->b * line.getDirection().getY();
	t_denum += this->c * line.getDirection().getZ();

	float t = -1 * (t_num / t_denum);

	float x = line.getDirection().getX() * t + line.getPoint().getX();
	float y = line.getDirection().getY() * t + line.getPoint().getY();
	float z = line.getDirection().getZ() * t + line.getPoint().getZ();

	return Point3d(x, y, z);
}