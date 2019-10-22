// -----
// Author: Jacob Holyfield
// File Name: PlayerAnimController.cpp
// Project: Chrono Pause
// -----

// Includes
#include <stdafx.h>
#include "PlayerAnimController.h"

#include <GameObject.h>			// Game Objects
#include <Transform.h>			// Transform
#include <Physics.h>			// Physics
#include <Sprite.h>				// Sprite
#include <Animation.h>			// Animation

Behaviors::PlayerAnimController::PlayerAnimController() : Component("PlayerAnimController")
{
	transform = nullptr;
	physics = nullptr;
	sprite = nullptr;
	animation = nullptr;
}

Component * Behaviors::PlayerAnimController::Clone() const
{
	return new PlayerAnimController(*this);
}

void Behaviors::PlayerAnimController::Initialize()
{
	// Initialize the transform and physics
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
	sprite = static_cast<Sprite*>(GetOwner()->GetComponent("Sprite"));
	animation = static_cast<Animation*>(GetOwner()->GetComponent("Animation"));

	animation->Play(1, 1, 0.01f, false);
}

void Behaviors::PlayerAnimController::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	// Get the player's previous velocity
	Vector2D velocity = physics->GetVelocity();

	if (animation->IsDone()) {
		if (velocity.y > 0.01f) {
			animation->Play(3, 1, 0.01f, true);
		}
		else if (velocity.y < -0.01f) {
			animation->Play(6, 1, 0.01f, true);
		}
		else if (velocity.x > 0.2f) {
			animation->Play(4, 2, 0.2f, true);
		}
		else if (velocity.x < -0.2f) {
			animation->Play(7, 2, 0.2f, true);
		}
		else {
			animation->Play(1, 1, 0.01f, true);
		}
	}
}
