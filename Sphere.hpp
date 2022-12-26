#ifndef CONSOLE_GRAPHICS_CPP_SPHERE_H_
#define CONSOLE_GRAPHICS_CPP_SPHERE_H_

#include "Point3d.hpp"
#include "Line3d.hpp"

class Sphere{
    Point3d center;
    float radius;

public:
    // Constructors
    Sphere(Point3d center, float radius = 1.0);

    // Getters
    Point3d getCenter() const;
    float getRadius() const;

    // Interactions
    bool isBelong(const Point3d& point);
    bool isIntersect(const Line3d& line);
};

#endif