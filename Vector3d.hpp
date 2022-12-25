#ifndef CONSOLE_GRAPHICS_CPP_VECTOR3D_H_
#define CONSOLE_GRAPHICS_CPP_VECTOR3D_H_

#include "Matrix.hpp"
#include <cmath>

class Vector3d{
    Matrix coordinates;
    float length;
public:
    // Constructors
    Vector3d(float x = 1.0, float y = 1.0, float z = 1.0);

    // Getters
    Matrix getCoordinates() const;
    float getLenght() const;

    // Norm
    Vector3d norm() const;  // Returns normalized vector

    // Arithmetical operations
    friend Vector3d operator+(Vector3d lhs, const Vector3d& rhs);
    friend Vector3d operator-(Vector3d lhs, const Vector3d& rhs);
    friend float    operator*(Vector3d lhs, const Vector3d& rhs);
    friend Vector3d operator*(float lhs, const Vector3d& rhs);
    friend Vector3d operator*(Vector3d lhs, const float& rhs);
};

#endif