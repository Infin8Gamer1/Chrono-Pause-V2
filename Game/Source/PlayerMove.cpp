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
#include <CameraController.h>	// Camera Controller
#include <Space.h>
#include "ExplosionTimer.h"
#include <Engine.h>
#include <SoundManager.h>
#include <Level.h>
#include <Space.h>
#include <Parser.h>

#include <Input.h>				// Input
#include <Graphics.h>

// Forward Declaration of Handler Functions
void Behaviors::PlayerMapCollisionHandler(GameObject& gameObject, const MapCollision& map);
void Behaviors::PlayerObjectCollisionHandler(GameObject& current, GameObject& other);

// Class Member Functions
// Constructor
Behaviors::PlayerMove::PlayerMove(float runSpeed, float jumpVelocity)
	: Component("PlayerMove"), holdingCube(nullptr), transform(nullptr), physics(nullptr), gravity(Vector2D(0,-600)), runSpeed(runSpeed), jumpVelocity(jumpVelocity),
	isGrounded(false), isHolding(false)
{
}

Component* Behaviors::PlayerMove::Clone() const
{
	return new PlayerMove(*this);
}

void Behaviors::PlayerMove::Initialize()
{
	isGrounded = false;
	isHolding = false;

	// Initialize the transform and physics
	transform = GetOwner()->GetComponent<Transform>();
	physics = GetOwner()->GetComponent<Physics>();
	physics->SetGravity(gravity);
		
	// Get the collider and set up the handlers
	Collider* collider = GetOwner()->GetComponent<Collider>();
	collider->SetCollisionHandler(PlayerObjectCollisionHandler);
	collider->SetMapCollisionHandler(PlayerMapCollisionHandler);
		
	// Set the jump sound
	Engine::GetInstance().GetModule<SoundManager>()->AddEffect("jump.wav");
}

void Behaviors::PlayerMove::Update(float dt)
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
			holdingCube->GetComponent<Transform>()->SetTranslation(transform->GetTranslation());
			holdingCube->GetComponent<Physics>()->SetGravity(Vector2D());
		} else if (!isHolding) {
			holdingCube->GetComponent<Physics>()->SetGravity(Vector2D(0,-100));
			holdingCube = nullptr;
		}
	}
}

void Behaviors::PlayerMove::DoMovement()
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

void Behaviors::PlayerMapCollisionHandler(GameObject& current, const MapCollision& map)
{
	// If we collided with the map from the bottom, then we are grounded, if we not we aren't grounded
	if (map.bottom)
	{
		current.GetComponent<PlayerMove>()->isGrounded = true;
	}
}

void Behaviors::PlayerObjectCollisionHandler(GameObject& current, GameObject& other)
{
	PlayerMove* playerMove = current.GetComponent<PlayerMove>();
	if (other.GetName() == "HelperCube")
	{
		playerMove->holdingCube = &other;
	}
	else if(other.GetName().find("Lava") != std::string::npos)
	{
		//create the explosion
		Parser* parse = new Parser("Assets/Objects/Explosion.object", std::fstream::in);

		GameObject* explosion = new GameObject("Explosion");

		try
		{
			explosion->Deserialize(*parse);
		}
		catch (ParseException e)
		{
			std::cout << e.what() << std::endl;

			//DisplayMessage(e.what());
		}

		delete parse;
		parse = nullptr;

		if (explosion != nullptr) {
			current.GetSpace()->GetObjectManager().AddObject(*explosion);

			Vector2D pos = current.GetComponent<Transform>()->GetTranslation();
			explosion->GetComponent<Transform>()->SetTranslation(pos);

			explosion->GetComponent<ExplosionTimer>()->Explode();
		}

		//destroy the player and retarget the camera to null
		current.GetSpace()->GetLevel()->cameraController->Retarget(static_cast<Transform*>(nullptr));
		current.Destroy();
	}
}