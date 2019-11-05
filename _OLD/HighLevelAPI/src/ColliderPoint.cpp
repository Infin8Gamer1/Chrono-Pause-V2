/**
	* Author: David Wong
	* Project: CS230 Lab 6
	* File Name: ColliderPoint.cpp
**/

// Includes //
#include "stdafx.h"
#include "ColliderPoint.h"

#include <Graphics.h>			// Graphics
#include <DebugDraw.h>			// Debug Draw

#include "GameObject.h"			// Game Object
#include "Transform.h"			// Transform
#include "ColliderCircle.h"		// Collider Circle
#include "ColliderRectangle.h"	// Collider Rectangle
#include "Intersection2D.h"		// Intersection Helper Functions

ColliderPoint::ColliderPoint()
	: Collider(ColliderType::ColliderTypePoint)
{
}

Component* ColliderPoint::Clone() const
{
	return new ColliderPoint(*this);
}

void ColliderPoint::Draw()
{
	Graphics& graphics(Graphics::GetInstance());
	DebugDraw& debugDraw(DebugDraw::GetInstance());
	debugDraw.AddCircle(transform->GetTranslation(), 10, graphics.GetCurrentCamera());
}

bool ColliderPoint::IsCollidingWith(const Collider& other) const
{
	GameObject* otherOwner = other.GetOwner();
	Transform* otherTransform = reinterpret_cast<Transform*>(otherOwner->GetComponent("Transform"));
	const Vector2D& position = transform->GetTranslation();
	switch (other.GetType())
	{
		case ColliderType::ColliderTypePoint:
			return AlmostEqual(otherTransform->GetTranslation(), position);

		case ColliderType::ColliderTypeCircle:
		{
			const ColliderCircle& colliderCircle = reinterpret_cast<const ColliderCircle&>(other);
			Circle circle1(otherTransform->GetTranslation(), colliderCircle.GetRadius());
			return PointCircleIntersection(position, circle1);
		}

		case ColliderType::ColliderTypeRectangle:
		{
			const ColliderRectangle& colliderRect = reinterpret_cast<const ColliderRectangle&>(other);
			BoundingRectangle rect(otherTransform->GetTranslation() + colliderRect.GetOffset(), colliderRect.GetExtents());
			return PointRectangleIntersection(position, rect);
		}

		default:
			return false;
			
	}
}