/**
	* Author: David Wong
	* Project: CS230 Lab 6
	* File Name: ColliderCircle.cpp
**/

// Includes //
#include "stdafx.h"
#include "ColliderCircle.h"

#include <Graphics.h>			// Graphics
#include <DebugDraw.h>			// DebugDraw
#include <Shapes2D.h>			// 2D Shapes

#include "Component.h"			// Component
#include "GameObject.h"			// Game Object
#include "Transform.h"			// Transform
#include "Intersection2D.h"		// Intersection Helper Functions
#include "ColliderRectangle.h"	// ColliderRectangle

ColliderCircle::ColliderCircle(float radius)
	: Collider(ColliderType::ColliderTypeCircle), radius(radius)
{
}

Component* ColliderCircle::Clone() const
{
	return new ColliderCircle(*this);
}

void ColliderCircle::Draw()
{
	DebugDraw& debug(DebugDraw::GetInstance());
	Graphics& graphics(Graphics::GetInstance());
	debug.AddCircle(transform->GetTranslation(), radius, graphics.GetCurrentCamera());
}

float ColliderCircle::GetRadius() const
{
	return radius;
}

void ColliderCircle::SetRadius(float radius_)
{
	radius = radius_;
}

bool ColliderCircle::IsCollidingWith(const Collider& collider) const
{
	Circle circle1(transform->GetTranslation(), radius);
	GameObject* otherColliderObject = collider.GetOwner();
	Transform* colliderTransform = reinterpret_cast<Transform*>(otherColliderObject->GetComponent("Transform"));
	const Vector2D& otherColliderTranslation = colliderTransform->GetTranslation();

	switch (collider.GetType())
	{
	case ColliderType::ColliderTypePoint:
		return PointCircleIntersection(otherColliderTranslation, circle1);

	case ColliderType::ColliderTypeCircle:
	{
		const ColliderCircle& otherColliderCircle = static_cast<const ColliderCircle&>(collider);
		Circle circle2(otherColliderTranslation, otherColliderCircle.radius);
		return CircleCircleIntersection(circle1, circle2);
	}

	case ColliderType::ColliderTypeRectangle:
	{
		const ColliderRectangle& otherColliderRect = static_cast<const ColliderRectangle&>(collider);
		BoundingRectangle rect(otherColliderTranslation + otherColliderRect.GetOffset(), otherColliderRect.GetExtents());
		return RectangleCircleIntersection(rect, circle1);
	}

	default:
		// Just in case we don't find a collider that we can solve for..?
		return false;
	}
}