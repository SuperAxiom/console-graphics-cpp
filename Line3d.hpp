#ifndef CONSOLE_GRAPHICS_CPP_LINE3D_H_
#define CONSOLE_GRAPHICS_CPP_LINE3D_H_

#include "Vector3d.hpp"
#include "Point3d.hpp"

class Line3d{
    Point3d point;
    Vector3d direction;
public:
    // Constructors
    Line3d(Point3d point, Vector3d direction);
    Line3d(Point3d point1, Point3d point2);

    // Getters
    Point3d getPoint() const;
    Vector3d getDirection() const;

    // Others
    bool isBelong(const Point3d& point);
    bool isParallel(const Line3d& line);
    Point3d findIntersection(const Line3d& line);
};

#endif