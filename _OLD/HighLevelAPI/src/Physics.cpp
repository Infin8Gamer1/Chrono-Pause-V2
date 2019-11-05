/**
	* Author: David Wong
	* Description: To describe how a physics object behaves
	* Project: CS230 Lab 5
**/

// Includes //
#include "stdafx.h"
#include "Physics.h"			// Physics

#include "Transform.h"			// Transform	
#include "GameObject.h"			// Game Object

Physics::Physics() : Component("Physics")
{
	// Velocity may be stored as a direction vector and speed scalar, instead.
	velocity = Vector2D(0,0);

	// Angular velocity, the speed and direction that the object rotates.
	angularVelocity = 0.0f;

	// Used when calculating acceleration due to forces.
	inverseMass = 1.0f;

	// The sum of all forces acting on an object
	forcesSum = Vector2D(0,0);

	// Acceleration = inverseMass * (sum of forces)
	acceleration = Vector2D(0,0);

	// Previous position.  May be used for resolving collisions.
	oldTranslation = Vector2D(0,0);

	// Transform component
	transform = nullptr;

	//the gravity that should get applyed
	gravity = Vector2D(0,0);
}



void Physics::Initialize()
{
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
}

Component* Physics::Clone() const
{
	return new Physics(*this);
}

void Physics::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	AddForce(gravity);

	acceleration = forcesSum * inverseMass;
	// Reset the forcases
	forcesSum = Vector2D();
}

void Physics::FixedUpdate(float dt)
{
	// Calculate the velocity
	velocity += acceleration * dt;
	// Save the Old Translation
	oldTranslation = transform->GetTranslation();
	// Update the translation
	Vector2D newTranslation(oldTranslation + velocity * dt);
	transform->SetTranslation(newTranslation);
	// Update the rotation
	transform->SetRotation(transform->GetRotation() + angularVelocity * dt);
}

// Accessors
const Vector2D& Physics::GetAcceleration() const
{
	return acceleration;
}

const Vector2D& Physics::GetVelocity() const
{
	return velocity;
}

float Physics::GetAngularVelocity() const
{
	return angularVelocity;
}

const Vector2D& Physics::GetOldTranslation() const
{
	return oldTranslation;
}

// Mutators
void Physics::SetVelocity(const Vector2D& velocity_)
{
	velocity = velocity_;
}

void Physics::SetAngularVelocity(float angularVelocity_)
{
	angularVelocity = angularVelocity_;
}

void Physics::SetGravity(Vector2D _gravity)
{
	gravity = _gravity;
}

Vector2D Physics::GetGravity()
{
	return gravity;
}

void Physics::SetMass(float mass_)
{
	inverseMass = 1.0f / mass_;
}

// Adds a one-frame force to the object
void Physics::AddForce(const Vector2D& force)
{
	forcesSum += force;
}