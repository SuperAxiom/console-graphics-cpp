#include "Line3d.hpp"

// Constructors
Line3d::Line3d(Point3d point, Vector3d direction){
    this->point = point;
    this->direction = direction.norm();
}

Line3d::Line3d(Point3d point1, Point3d point2){
    Vector3d direction = Vector3d(point1, point2).norm();
    Line3d(point1, direction);
}

// Getters
Point3d Line3d::getPoint() const{
    return this->point;
}

Vector3d Line3d::getDirection() const{
    return this->direction;
}

// Others
bool Line3d::isBelong(const Point3d& point){
    float x = point.getX();
    float y = point.getY();
    float z = point.getZ();

    float t1 = (x - this->point.getX()) / this->direction.getX();
    float t2 = (y - this->point.getY()) / this->direction.getY();
    float t3 = (z - this->point.getZ()) / this->direction.getZ();

    if (t1 == t2 && t2 == t3)
        return true;
    return false;
}

bool Line3d::isParallel(const Line3d& line){
    if (this->direction == line.direction)
        return true;

    if (this->direction == -1 * line.direction)
        return true;

    return false;
}

Point3d Line3d::findIntersection(const Line3d& line){
    if (this->isParallel(line))
        throw "NoIntersectionError";
    
    float t = (line.getPoint().getX() - this->point.getX()) / (this->direction.getX() - line.direction.getX());

    float x = this->direction.getX() * t + this->point.getX();
    float y = this->direction.getY() * t + this->point.getY();
    float z = this->direction.getZ() * t + this->point.getZ();

    return Point3d(x, y, z);
}