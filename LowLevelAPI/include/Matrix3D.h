//------------------------------------------------------------------------------
//
// File Name:	Matrix3D.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		Beta Engine
// Course:		WANIC VGP2
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations
//------------------------------------------------------------------------------

class Vector3D;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Frequently, vector and matrix structures are declared publicly.  While an
// interface is typically provided with these structures, these are two common
// exceptions to the coding best practice of "hiding information".

class Matrix3D
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor for matrix. Sets all data in matrix to 0.
	Matrix3D();

	// This function creates an identity matrix and returns it.
	static Matrix3D IdentityMatrix();

	// Transformation matrices
	static Matrix3D TranslationMatrix(const Vector3D& position);
	static Matrix3D RotationMatrixOrthogonal(const Vector3D& u, const Vector3D& v, const Vector3D& w);
	static Matrix3D OrthogonalProjectionMatrix(float width, float height, float nearDepth, float farDepth);
	static Matrix3D OrthogonalProjectionMatrix(float left, float right, float bottom, 
		float top, float nearDepth, float farDepth);
	static Matrix3D LookAtMatrix(const Vector3D& position, const Vector3D& target, const Vector3D& up);

	// This function calculates the transpose matrix of Mtx and saves it in the result matrix.
	// (NOTE: Care must be taken when pResult = pMtx.)
	Matrix3D Transposed() const;

	// Attempts to find the inverse of the matrix.
	// Params:
	//   result = The matrix that will store the inverse, if an inverse exists.
	// Return:
	//   If there is no inverse, returns false, otherwise returns true.
	bool Inverse(Matrix3D& result) const;

	// This function multiplies the current matrix with another and returns the result as a new matrix.
	// HINT: Use the RowColumnMultiply function to help write this function.
	Matrix3D operator*(const Matrix3D& other) const;

	// This function multiplies the current matrix with another, storing the result in the current matrix.
	// HINT: Use the RowColumnMultiply function to help write this function.
	Matrix3D& operator*=(const Matrix3D& other);

	// This function multiplies a matrix with a vector and returns the result as a new vector.
	// Result = Mtx * Vec.
	Vector3D operator*(const Vector3D& vec) const;

	//------------------------------------------------------------------------------
	// Public Data
	//------------------------------------------------------------------------------

	// The matrix is stored in column-major format, meaning the consecutive
	//   elements of columns are contiguous.
	//   m[row][column]
	union
	{
		float m[4][4];
		float v[16];
	};

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Multiplies a row of the current matrix by a column in another and returns the result.
	float RowColumnMultiply(const Matrix3D& other, unsigned row, unsigned col) const;
};
//------------------------------------------------------------------------------
