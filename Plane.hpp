#ifndef CONSOLE_GRAPHICS_CPP_PLANE_H_
#define CONSOLE_GRAPHICS_CPP_PLANE_H_

#include "Line3d.hpp"
#include "Point3d.hpp"

class Plane{
    float a;
    float b;
    float c;
    float d;

public:
    // Constructors
    Plane(float a = 1.0, float b = 1.0, float c = 1.0, float d = 0.0);

    // Getters
    Matrix getParams() const;
    Vector3d getNormVector() const;
    float getD() const;

    // Interactions
    bool isBelong(const Point3d& point);
    bool isIntersect(const Line3d& line);
    Point3d findIntersection(const Line3d& line);
};

#endif