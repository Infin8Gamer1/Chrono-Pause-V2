#pragma once
// -----
// Author: David Wong
// File Name: PlayerMove.h
// Project: Chrono Pause
// -----

// Includes
#include <Component.h>
#include <Vector2D.h>

// Forward Declaration
class Physics;
class Transform;
struct MapCollision;


// Class Declaration
namespace Behaviors
{

	class PlayerMove : public Component
	{
	private:
		// Keep track of the cube we are currently holding
		GameObject* holdingCube;
		// The object's transform
		Transform* transform;
		// The object's physics
		Physics* physics;
		// Acceleration due to gravity
		const Vector2D gravity;
		// The object's horizontal speed
		float runSpeed, jumpVelocity;
		// Whether the player is grounded or not
		bool isGrounded;

		bool isHolding;

	public:
		// Default Constructor
		// Params:
		//   runSpeed: The player's run speed
		//   jumpVelocity: The player's jump velocity
		PlayerMove(float runSpeed = 100.0f, float jumpVelocity = 500.0f);
		// Public overwritten methods
		Component* Clone() const override;
		// Initializes the component
		void Initialize() override;
		// Updates the player move script
		// Params:
		//   dt: The delta time between frames
		void Update(float dt) override;
		// Helper function for movement options
		void DoMovement();
		// The collision handler functions
		// Handles the map collisions
		// Params:
		//   gameObject: The current object
		//   map: The map we are colliding with
		friend void PlayerMapCollisionHandler(GameObject& gameObject, const MapCollision& map);
		// Handles the collisions with other objects
		// Params:
		//   current: The current object colliding
		//   other: The other object
		friend void PlayerObjectCollisionHandler(GameObject& current, GameObject& other);
	};
}