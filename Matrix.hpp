/*
 * Matrix.h
 *
 *  Created on: Dec 23, 2022
 *      Author: vladyslav
 */

#ifndef CONSOLE_GRAPHICS_CPP_MATRIX_H_
#define CONSOLE_GRAPHICS_CPP_MATRIX_H_

#include <iostream>

using namespace std;

class Matrix {
	uint columns;
	uint rows;
	float** matr;

public:
	// Constructors
	Matrix(uint rows = 2, uint columns = 2);	// Creates zero matrix
	Matrix(float** matr, uint rows, uint columns);
	Matrix(float* values, uint size);	// Create matrix size x 1 with given values
	Matrix(const Matrix& matrix);		// Copy constructor

	// Destructors
	~Matrix();

	// Getters
	uint getColumns() const;
	uint getRows() const;
	float getValue(uint i, uint j) const;

	// Setters
	void setValue(float value, uint i, uint j);

	// Returns transpose matrix
	Matrix transpose() const;

	// Arithmetical operators
	friend Matrix operator+(Matrix lhs, const Matrix& rhs);
	friend Matrix operator-(Matrix lhs, const Matrix& rhs);
	friend Matrix operator*(Matrix lhs, const Matrix& rhs);
	friend Matrix operator*(float lhs, const Matrix& rhs);
	friend Matrix operator*(const Matrix& lhs, float rhs);
	friend bool   operator==(const Matrix& lhs, const Matrix& rhs);
};

#endif /* CONSOLE_GRAPHICS_CPP_MATRIX_H_ */
