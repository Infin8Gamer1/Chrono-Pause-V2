/**
* Author: David Wong
* Project: CS230 Lab 6
* File Name: ColliderRectangle.cpp
**/

// Includes //
#include "stdafx.h"
#include "ColliderRectangle.h"

#include <Vector2D.h>			// Vector 2D
#include <Graphics.h>			// Graphics
#include <DebugDraw.h>			// Debug Draw
#include <Physics.h>
#include <Transform.h>

#include "GameObject.h"			// Game Object
#include "Transform.h"			// Transform
#include "Intersection2D.h"		// 2D Intersection Helper Functions
#include "ColliderCircle.h"		// Collider Circle

// Public Member Functions //
ColliderRectangle::ColliderRectangle(const Vector2D& extents, const Vector2D offset)
	: Collider(ColliderType::ColliderTypeRectangle), extents(extents), offset(offset)
{

}

Component* ColliderRectangle::Clone() const
{
	return new ColliderRectangle(*this);
}

void ColliderRectangle::Draw()
{
	Graphics& graphics = Graphics::GetInstance();
	DebugDraw& debugDraw = DebugDraw::GetInstance();

	debugDraw.AddRectangle(transform->GetTranslation() + GetOffset(), extents, graphics.GetDefaultCamera());
}

const Vector2D& ColliderRectangle::GetExtents() const
{
	return extents;
}

void ColliderRectangle::SetExtents(const Vector2D& extents_)
{
	extents = extents_;
}

const Vector2D & ColliderRectangle::GetOffset() const
{
	return offset;
}

void ColliderRectangle::SetOffset(const Vector2D & offset_)
{
	offset = offset_;
}

bool ColliderRectangle::IsCollidingWith(const Collider& other) const
{
	GameObject* otherOwner = other.GetOwner();
	Transform* otherTransform = reinterpret_cast<Transform*>(otherOwner->GetComponent("Transform"));
	const Vector2D& position = transform->GetTranslation() + GetOffset();
	const Vector2D& otherPosition = otherTransform->GetTranslation();

	BoundingRectangle rect(position, extents);

	switch (other.GetType())
	{
	case ColliderType::ColliderTypePoint:
		return PointRectangleIntersection(otherPosition, rect);
	case ColliderType::ColliderTypeCircle:
	{
		const ColliderCircle& colliderCircle = reinterpret_cast<const ColliderCircle&>(other);
		Circle circle(otherPosition, colliderCircle.GetRadius());
		return RectangleCircleIntersection(rect, circle);
	}
	case ColliderType::ColliderTypeRectangle:
	{
		const ColliderRectangle& colliderRect = reinterpret_cast<const ColliderRectangle&>(other);
		BoundingRectangle otherRect(otherPosition + colliderRect.offset, colliderRect.extents);
		return RectangleRectangleIntersection(rect, otherRect);
	}
	default:
		return false;
	}
}