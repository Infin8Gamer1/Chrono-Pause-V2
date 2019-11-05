/**
	* Author: David Wong
	* Description: Define the Transform component
	* Project: CS230 Lab 5
**/

// Includes //
#include "stdafx.h"
#include "Transform.h"

#include "Matrix2DStudent.h"			// Matrix2D


// Public Member Functions //
Transform::Transform(float x, float y)
	: Component("Transform"), translation(x, y), scale(50, 50), rotation(0), isDirty(true)
{
	matrix = GetMatrix();
}

Transform::Transform(Vector2D translation, Vector2D scale, float rotation)
	: Component("Transform"), translation(translation), scale(scale), rotation(rotation), isDirty(true)
{
	matrix = GetMatrix();
}

Component* Transform::Clone() const
{
	return new Transform(*this);
}

const CS230::Matrix2D& Transform::GetMatrix()
{
	// If the transformations had changed, then re-construct the matrix
	CalculateMatrices();
	return matrix;
}

const CS230::Matrix2D& Transform::GetInverseMatrix()
{
	// Update the inverse transformation if it has changed
	CalculateMatrices();
	return inverseMatrix;
}

void Transform::CalculateMatrices()
{
	// If the transformations had changed, then re-construct the matrix
	if (isDirty)
	{
		matrix = CS230::Matrix2D::TranslationMatrix(translation.x, translation.y)
			* CS230::Matrix2D::RotationMatrixRadians(rotation) * CS230::Matrix2D::ScalingMatrix(scale.x, scale.y);

		inverseMatrix = CS230::Matrix2D::ScalingMatrix(1.0f / scale.x, 1.0f / scale.y)
			* CS230::Matrix2D::RotationMatrixRadians(-rotation) * CS230::Matrix2D::TranslationMatrix(-translation.x, -translation.y);

		isDirty = false;
	}
}

// Accesors //
const Vector2D& Transform::GetTranslation() const
{
	return translation;
}

const Vector2D& Transform::GetScale() const
{
	return scale;
}

float Transform::GetRotation() const
{
	return rotation;
}

// Mutators //
void Transform::SetTranslation(const Vector2D& translation_)
{
	if (translation_.x == translation.x && translation_.y == translation.y)
		return;

	translation = translation_;
	isDirty = true;
}

void Transform::SetScale(const Vector2D& scale_)
{
	if (scale_.x == scale.x && scale_.y == scale.y)
		return;

	scale = scale_;
	isDirty = true;
}

void Transform::SetRotation(float rotation_)
{
	if (rotation_ == rotation)
		return;

	rotation = rotation_;
	isDirty = true;
}