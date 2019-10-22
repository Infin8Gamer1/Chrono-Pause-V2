/**
	* Author: David Wong
	* Project: CS230 Lab 6
	* File Name: Collider.cpp
**/

// Includes //
#include "stdafx.h"
#include "Collider.h"

#include "GameObject.h"			// Game Object

// Public Member Functions //
Collider::Collider(ColliderType type)
	: Component("Collider"), type(type), handler(nullptr), mapHandler(nullptr), enabled(true)
{
}

MapCollision::MapCollision(bool bottom, bool top, bool left, bool right)
	: bottom(bottom), top(top), left(left), right(right)
{
}

void Collider::Initialize()
{
	transform = reinterpret_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	physics = reinterpret_cast<Physics*>(GetOwner()->GetComponent("Physics"));
}

void Collider::CheckCollision(const Collider& other)
{
	if (IsCollidingWith(other) && handler && enabled && other.enabled)
	{
		handler(*GetOwner(), *other.GetOwner());
	}
}

void Collider::SetEnabled(bool enabled_)
{
	enabled = enabled_;
}

bool Collider::IsEnabled() const
{
	return enabled;
}

ColliderType Collider::GetType() const
{
	return type;
}

void Collider::SetCollisionHandler(CollisionEventHandler ptr)
{
	handler = ptr;
}

void Collider::SetMapCollisionHandler(MapCollisionEventHandler ptr)
{
	mapHandler = ptr;
}

MapCollisionEventHandler Collider::GetMapCollisionHandler() const
{
	return mapHandler;
}