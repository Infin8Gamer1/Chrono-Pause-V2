//------------------------------------------------------------------------------
//
// File Name:	ColliderRectangle.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Collider.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class ColliderRectangle : public Collider
{
public:
	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor for rectangle collider.
	// Params:
	//   extents = The rectangle's extents (half-width, half-height).
	ColliderRectangle(const Vector2D& extents = Vector2D(50.0f, 50.0f), const Vector2D offset = Vector2D(0,0));

	// Clone an collider and return a pointer to the cloned object.
	// Returns:
	//   A pointer to a collider.
	Component* Clone() const;

	// Debug drawing for colliders.
	void Draw() override;

	// Get the rectangle collider's extents (half-width, half-height).
	// Returns:
	//	 The extents of the rectangle.
	const Vector2D& GetExtents() const;

	// Set the rectangle collider's extents (half-width, half-height).
	// Params:
	//   extents = The new extents of the rectangle.
	void SetExtents(const Vector2D& extents);

	// Get the rectangle collider's offset.
	// Returns:
	//	 The extents of the rectangle.
	const Vector2D& GetOffset() const;

	// Set the rectangle collider's offset.
	// Params:
	//   offset = the offset from the parent.
	void SetOffset(const Vector2D& offset);

	// Check for collision between a circle and another arbitrary collider.
	// Params:
	//	 other = Reference to the second circle collider component.
	// Returns:
	//	 Return the results of the collision check.
	bool IsCollidingWith(const Collider& other) const override;

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Extents of the rectangle collider.
	Vector2D extents;
	//the offset of the collider
	Vector2D offset;
};

//------------------------------------------------------------------------------
