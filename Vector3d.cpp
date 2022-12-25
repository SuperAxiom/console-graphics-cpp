#include "Vector3d.hpp"


// Constructors
Vector3d::Vector3d(float x, float y, float z){
    float values[3] = {x, y, z};
    
    this->coordinates = Matrix(values, 3);
    this->length = sqrt(x*x + y*y + z*z);
}

Vector3d::Vector3d(Point3d begin, Point3d end){
    float x = end.getX() - begin.getX();
    float y = end.getY() - begin.getY();
    float z = end.getZ() - begin.getZ();

    Vector3d(x, y, z);
}

// Getters
Matrix Vector3d::getCoordinates() const{
    return this->coordinates;
}

float Vector3d::getLenght() const{
    return this->length;
}

// Norm
Vector3d Vector3d::norm() const{
    float x, y, z;
    x = this->coordinates.getValue(0, 0) / this->length;
    y = this->coordinates.getValue(1, 0) / this->length;
    z = this->coordinates.getValue(2, 0) / this->length;

    return Vector3d(x, y, z);
}


// Arithmetical operations
Vector3d operator+(Vector3d lhs, const Vector3d& rhs){
    Matrix lhs_coor = lhs.getCoordinates();
    Matrix rhs_coor = rhs.getCoordinates();

    float x = lhs_coor.getValue(0, 0) + rhs_coor.getValue(0, 0);
    float y = lhs_coor.getValue(1, 0) + rhs_coor.getValue(1, 0);
    float z = lhs_coor.getValue(2, 0) + rhs_coor.getValue(2, 0);

    return Vector3d(x, y, z);
}

Vector3d operator-(Vector3d lhs, const Vector3d& rhs){
    Matrix lhs_coor = lhs.getCoordinates();
    Matrix rhs_coor = rhs.getCoordinates();

    float x = lhs_coor.getValue(0, 0) - rhs_coor.getValue(0, 0);
    float y = lhs_coor.getValue(1, 0) - rhs_coor.getValue(1, 0);
    float z = lhs_coor.getValue(2, 0) - rhs_coor.getValue(2, 0);

    return Vector3d(x, y, z);
}

float operator*(Vector3d lhs, const Vector3d& rhs){
    Matrix lhs_coor = lhs.getCoordinates();
    Matrix rhs_coor = rhs.getCoordinates();

    float result = 0;
    
    result += lhs_coor.getValue(0, 0) * rhs_coor.getValue(0, 0);
    result += lhs_coor.getValue(1, 0) * rhs_coor.getValue(1, 0);
    result += lhs_coor.getValue(2, 0) * rhs_coor.getValue(2, 0);

    return result;
}

Vector3d operator*(float lhs, const Vector3d& rhs){
    Matrix rhs_coor = rhs.getCoordinates();

    float x = lhs * rhs_coor.getValue(0, 0);
    float y = lhs * rhs_coor.getValue(1, 0);
    float z = lhs * rhs_coor.getValue(2, 0);

    return Vector3d(x, y, z);
}

Vector3d operator*(Vector3d lhs, const float& rhs){
    Matrix lhs_coor = lhs.getCoordinates();

    float x = rhs * lhs_coor.getValue(0, 0);
    float y = rhs * lhs_coor.getValue(1, 0);
    float z = rhs * lhs_coor.getValue(2, 0);

    return Vector3d(x, y, z);  
}