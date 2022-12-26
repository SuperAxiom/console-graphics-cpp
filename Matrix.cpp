/*
 * Matrix.cpp
 *
 *  Created on: Dec 23, 2022
 *      Author: vladyslav
 */

#include "Matrix.hpp"

// Constructors
Matrix::Matrix(uint rows, uint columns){
	this->rows = rows;
	this->columns = columns;

	// Allocating memory
	this->matr = new float*[rows];
	for (uint i = 0; i < rows; i++)
		*(this->matr + i) = new float[columns];

	// Filling with zeros
	for (uint i = 0; i < rows; i++)
		for (uint j = 0; j < columns; j++)
			*(*(this->matr + i) + j) = 0.0;
}

Matrix::Matrix(float** matr, uint rows, uint columns){
	this->rows = rows;
	this->columns = columns;

	// Allocating memory
	this->matr = new float*[rows];
	for (uint i = 0; i < rows; i++)
		*(this->matr + i) = new float[columns];

	// Copying array
	for (uint i = 0; i < rows; i++)
		for (uint j = 0; j < columns; j++)
			*(*(this->matr + i) + j) = matr[i][j];
}

Matrix::Matrix(float* values, uint size){
	this->rows = size;
	this->columns = 1;

	// Allocating memory
	this->matr = new float*[rows];
	for (uint i = 0; i < rows; i++)
		*(this->matr + i) = new float[columns];

	// Copying values
	for (uint i = 0; i < size; i++)
		this->matr[i][0] = values[i];
}

Matrix::Matrix(const Matrix& matrix){
	this->rows = matrix.rows;
	this->columns = matrix.columns;
	
	// Allocating memory
	this->matr = new float*[this->rows];
	for (uint i = 0; i < this->rows; i++)
		*(this->matr + i) = new float[this->columns];

	// Copying values
	for (uint i = 0; i < this->rows; i++)
		for (uint j = 0; j < this->columns; j++)
			this->matr[i][j] = matrix.matr[i][j];
}

// Destructors
Matrix::~Matrix(){
	for (uint i = 0; i < rows; i++)
		delete [] (*(this->matr + i));
	delete [] this->matr;
}


// Getters
uint Matrix::getColumns() const{
	return this->columns;
}

uint Matrix::getRows() const{
	return this->rows;
}

float Matrix::getValue(uint i, uint j) const{
	return this->matr[i][j];
}


// Setters
void Matrix::setValue(float value, uint i, uint j){
	try{
		this->matr[i][j] = value;
	}
	catch(const std::exception& e){
		throw e;
	}
	
	
}


// Returns transpose matrix
Matrix Matrix::transpose() const{
	Matrix result(this->columns, this->rows);

	for (uint i = 0; i < result.rows; i++)
		for (uint j = 0; j < result.columns; j++)
			result.matr[i][j] = this->matr[j][i];

	return result;
}

// Display
void Matrix::display() const{
	for (uint i = 0; i < this->rows; i++){
		for (uint j = 0; j < this->columns; j++){
			cout << setw(3) << this->matr[i][j] << " ";
		}
		cout << endl;
		cout << endl;
	}
	cout << endl;
}

// Arithmetical operators
Matrix operator+(Matrix lhs, const Matrix& rhs){
	if (lhs.columns != rhs.columns || lhs.rows != rhs.rows)
		throw "SizeError";

	Matrix result(lhs.rows, lhs.columns);

	for (uint i = 0; i < result.rows; i++)
		for (uint j = 0; j < result.columns; j++)
			result.matr[i][j] = lhs.matr[i][j] + rhs.matr[i][j];

	return result;
}

Matrix operator-(Matrix lhs, const Matrix& rhs){
	if (lhs.columns != rhs.columns || lhs.rows != rhs.rows)
		throw "SizeError";

	Matrix result(lhs.rows, lhs.columns);

	for (uint i = 0; i < result.rows; i++)
		for (uint j = 0; j < result.columns; j++)
			result.matr[i][j] = lhs.matr[i][j] - rhs.matr[i][j];

	return result;
}

Matrix operator*(Matrix lhs, const Matrix& rhs){
	if (lhs.columns != rhs.rows)
		throw "SizeError";

	Matrix result(lhs.rows, rhs.columns);

	for (uint i = 0; i < result.rows; i++){
		for (uint j = 0; j < result.columns; j++){
			float sum = 0;
			for (uint k = 0; k < lhs.columns; k++)
				sum += lhs.matr[i][k] * rhs.matr[k][j];
			result.matr[i][j] = sum;
		}
	}

	return result;
}

Matrix operator*(float lhs, const Matrix& rhs){
	Matrix result(rhs.rows, rhs.columns);

	for (uint i = 0; i < result.rows; i++)
		for (uint j = 0; j < result.columns; j++)
			result.matr[i][j] = lhs * rhs.matr[i][j];

	return result;
}

Matrix operator*(const Matrix& lhs, float rhs){
	Matrix result(lhs.rows, lhs.columns);

	for (uint i = 0; i < result.rows; i++)
		for (uint j = 0; j < result.columns; j++)
			result.matr[i][j] = rhs * lhs.matr[i][j];

	return result;
}

bool operator==(const Matrix& lhs, const Matrix& rhs){
	if (lhs.columns != rhs.columns)
		return false;

	if (lhs.rows != rhs.rows)
		return false;
	
	for (uint i = 0; i < lhs.rows; i++)
		for (uint j = 0; j < lhs.columns; j++)
			if (lhs.matr[i][j] != rhs.matr[i][j])
				return false;
	
	return true;
}