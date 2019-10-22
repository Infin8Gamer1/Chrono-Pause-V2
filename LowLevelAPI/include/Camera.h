//------------------------------------------------------------------------------
//
// File Name:	Camera.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		Project 7
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Vector2D.h"
#include "Matrix3D.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Camera
{
public:
	Camera();

	const Matrix3D& GetViewMatrix();
	const Matrix3D& GetInverseViewMatrix();

	const Vector2D& GetTranslation() const;
	void SetTranslation(const Vector2D& translation);

	float GetDistance() const;
	void SetDistance(float value);

	float GetFOV() const;
	float GetNearClip() const;
	float GetFarClip() const;

	float GetRotation() const;
	void SetRotation(float rotation);

	static float distanceOffset;

private:
	// Helper functions
	void CalculateViewMatrix();

	// Member data
	Vector2D translation;
	bool isDirty;
	Matrix3D viewMatrix;
	Matrix3D inverseViewMatrix;

	float distance;
	float FOV;
	float nearClip;
	float farClip;
	float rotation;
};

//------------------------------------------------------------------------------
