// -----
// Author: David Wong
// File Name: PlayerMove.cpp
// Project: Chrono Pause
// -----

// Includes
#include <stdafx.h>
#include "PlayerMove.h"

#include <GameObject.h>			// Game Objects
#include <Transform.h>			// Transform
#include <Physics.h>			// Physics
#include <Sprite.h>				// Sprite
#include <ColliderTilemap.h>	// Tilemap Collider
#include "CameraController.h"	// Camera Controller
#include <Space.h>
#include "ExplosionTimer.h"
#include <Engine.h>
#include <SoundManager.h>

#include <Input.h>				// Input

namespace Behaviors
{
	// Forward Declaration of Handler Functions
	void PlayerMapCollisionHandler(GameObject& gameObject, const MapCollision& map);
	void PlayerObjectCollisionHandler(GameObject& current, GameObject& other);

	// Class Member Functions
	// Constructor
	PlayerMove::PlayerMove(float runSpeed, float jumpVelocity)
		: Component("PlayerMove"), holdingCube(nullptr), transform(nullptr), physics(nullptr), gravity(Vector2D(0,-600)), runSpeed(runSpeed), jumpVelocity(jumpVelocity),
		isGrounded(false), isHolding(false)
	{
	}

	Component* PlayerMove::Clone() const
	{
		return new PlayerMove(*this);
	}

	void PlayerMove::Initialize()
	{
		isGrounded = false;
		isHolding = false;

		// Initialize the transform and physics
		transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
		physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
		physics->SetGravity(gravity);
		
		// Get the collider and set up the handlers
		Collider* collider = static_cast<Collider*>(GetOwner()->GetComponent("Collider"));
		collider->SetCollisionHandler(PlayerObjectCollisionHandler);
		collider->SetMapCollisionHandler(PlayerMapCollisionHandler);
		
		// Set the jump sound
		Engine::GetInstance().GetModule<SoundManager>()->AddEffect("jump.wav");
	}

	void PlayerMove::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		
		//do the movement code
		DoMovement();

		if (physics->GetVelocity().y < 0) {
			isGrounded = false;
		}

		// Holding the cube
		if (holdingCube)
		{
			if (Input::GetInstance().CheckTriggered('E') && !isHolding) {
				isHolding = true;
			}
			else if (Input::GetInstance().CheckTriggered('E') && isHolding) {
				isHolding = false;
			}

			// Grab the cube if is holding is true
			if (isHolding)
			{
				static_cast<Transform*>(holdingCube->GetComponent("Transform"))->SetTranslation(transform->GetTranslation());
				static_cast<Physics*>(holdingCube->GetComponent("Physics"))->SetGravity(Vector2D());
			} else if (!isHolding) {
				static_cast<Physics*>(holdingCube->GetComponent("Physics"))->SetGravity(Vector2D(0,-100));
				holdingCube = nullptr;
			}
		}
	}

	void PlayerMove::DoMovement()
	{
		static const Input& input = Input::GetInstance();

		Vector2D velocity = physics->GetVelocity();
		Vector2D oldVelocity = velocity;
		//do air risistance and ground risistance
		if (isGrounded) {
			velocity += Vector2D(-oldVelocity.x / 4, 0);
		}
		else {
			velocity += Vector2D(-oldVelocity.x / 6, 0);
		}

		// Move the player horiztonally
		Vector2D scale = transform->GetScale();
		if (input.IsKeyDown('A'))
		{
			// If the a key is held, then move the player towards the left
			if (!isGrounded) {
				velocity.x -= runSpeed / 1.2f;
			}
			else {
				velocity.x -= runSpeed;
			}

			//cap speed at runSpeed
			if (velocity.x < -runSpeed * 2.5f) {
				velocity.x = -runSpeed * 2.5f;
			}
		}
		
		if (input.IsKeyDown('D'))
		{
			// If the d key is held, then move the player towards the right
			if (!isGrounded) {
				velocity.x += runSpeed / 1.2f;
			}
			else {
				velocity.x += runSpeed;
			}

			//cap speed at runSpeed
			if (velocity.x > runSpeed * 2.5f) {
				velocity.x = runSpeed * 2.5f;
			}
		}

		// Make the player jump if pressing the W key
		if (input.IsKeyDown('W') && isGrounded)
		{
			// Apply a velocity upwards
			velocity.y = jumpVelocity;
			isGrounded = false;
			// Only play the sound effect once
			if(input.CheckTriggered('W'))
				Engine::GetInstance().GetModule<SoundManager>()->PlaySound("jump.wav");

		}

		// Set the velocity of the physics object
		physics->SetVelocity(velocity);
	}

	void PlayerMapCollisionHandler(GameObject& current, const MapCollision& map)
	{
		// If we collided with the map from the bottom, then we are grounded, if we not we aren't grounded
		if (map.bottom)
		{
			static_cast<PlayerMove*>(current.GetComponent("PlayerMove"))->isGrounded = true;
		}
	}

	void PlayerMove::SetCameraController(CameraController* cameraController_)
	{
		cameraController = cameraController_;
	}

	void PlayerObjectCollisionHandler(GameObject& current, GameObject& other)
	{
		PlayerMove* playerMove = static_cast<PlayerMove*>(current.GetComponent("PlayerMove"));
		if (other.GetName() == "HelperCube")
		{
			playerMove->holdingCube = &other;
		}
		else if(other.GetName() == "Hazard")
		{
			//create the explosion
			GameObject* explosion = new GameObject(*current.GetSpace()->GetObjectManager().GetArchetypeByName("Explosion"));
			if (explosion != nullptr) {
				current.GetSpace()->GetObjectManager().AddObject(*explosion);

				Vector2D pos = static_cast<Transform*>(current.GetComponent("Transform"))->GetTranslation();
				static_cast<Transform*>(explosion->GetComponent("Transform"))->SetTranslation(pos);

				static_cast<ExplosionTimer*>(explosion->GetComponent("ExplosionTimer"))->Explode();
			}

			//destroy the player
			playerMove->cameraController->Retarget(static_cast<Transform*>(nullptr));
			current.Destroy();
		}
	}
}