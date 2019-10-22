/**
	* Author: David Wong
	* Description: Create the Matrix2D object
	* Project: CS230 Lab 5
**/

// Includes //
#include "stdafx.h"
#include "Matrix2DStudent.h"

#include <Vector2D.h>				// Vector2D //

namespace CS230
{
	// Private Member Functions //
	float Matrix2D::RowColumnMultiply(const Matrix2D& other, unsigned row, unsigned column) const
	{
		// Find the dot product of the vectors within this and the other matrix
		return m[row][0] * other.m[0][column] + m[row][1] * other.m[1][column] + m[row][2] * other.m[2][column];
	}

	// Public Member Functions //
	Matrix2D::Matrix2D()
	{
		// Zero out all of the matrix's components
		for (unsigned i = 0; i < 9; ++i)
		{
			m[i / 3][i % 3] = 0;
		}
	}

	Matrix2D Matrix2D::IdentityMatrix()
	{
		Matrix2D identity;
		// Create the identity part of the identity matrix
		for (unsigned i = 0; i < 3; ++i)
		{
			identity.m[i][i] = 1;
		}

		return identity;
	}

	Matrix2D Matrix2D::Transposed() const
	{
		Matrix2D transposed;
		// Create a copy of this matrix, but transposed
		for (unsigned i = 0; i < 9; ++i)
		{
			transposed.m[i % 3][i / 3] = m[i / 3][i % 3];
		}

		return transposed;
	}

	Matrix2D Matrix2D::TranslationMatrix(float x, float y)
	{
		Matrix2D translated(IdentityMatrix());
		translated.m[0][2] = x;
		translated.m[1][2] = y;

		return translated;
	}

	Matrix2D Matrix2D::ScalingMatrix(float x, float y)
	{
		Matrix2D scaled(IdentityMatrix());
		scaled.m[0][0] = x;
		scaled.m[1][1] = y;

		return scaled;
	}

	Matrix2D Matrix2D::RotationMatrixRadians(float angle)
	{
		Matrix2D rotated(IdentityMatrix());
		rotated.m[0][0] = cosf(angle);
		rotated.m[0][1] = -sinf(angle);
		rotated.m[1][0] = sinf(angle);
		rotated.m[1][1] = cosf(angle);

		return rotated;
	}

	Matrix2D Matrix2D::RotationMatrixDegrees(float angle)
	{
		return RotationMatrixRadians(angle * static_cast<float>(M_PI) / 180.0f);
	}

	Matrix2D Matrix2D::operator*(const Matrix2D& other) const
	{
		Matrix2D result(IdentityMatrix());
		// Multiply the two matrices
		for (unsigned i = 0; i < 3; ++i)
		{
			for (unsigned j = 0; j < 3; ++j)
			{
				result.m[i][j] = RowColumnMultiply(other, i, j);
			}
		}
		return result;
	}

	Matrix2D& Matrix2D::operator*=(const Matrix2D& other)
	{
		// Create a temporal matrix that stores the result
		// Then copy its remains to this matrix
		Matrix2D copy = *this * other;
		*this = copy;
		// Then return the instance of this matrix so that we can chain the multiplications toghether
		return *this;
	}

	Vector2D Matrix2D::operator*(const Vector2D& other) const
	{
		Vector2D result;
		
		// Multiply the vector and the matrix, and save into 'result'
		result.x = m[0][0] * other.x + m[0][1] * other.y + m[0][2];
		result.y = m[1][0] * other.x + m[1][1] * other.y + m[1][2];

		return result;
	}
}