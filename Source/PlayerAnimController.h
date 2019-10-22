#pragma once
// -----
// Author: Jacob Holyfield
// File Name: PlayerAnimController.h
// Project: Chrono Pause
// -----

// Includes
#include <Component.h>
#include <Vector2D.h>

// Forward Declaration
class Physics;
class Transform;
class Sprite;
class Animation;

// Class Declaration
namespace Behaviors
{

	class PlayerAnimController : public Component
	{
	private:
		// The object's transform
		Transform* transform;
		// The object's physics
		Physics* physics;
		// The object's sprite
		Sprite* sprite;
		// The object's animation
		Animation* animation;


	public:
		// Default Constructor
		// Params:
		PlayerAnimController();
		// Public overwritten methods
		Component* Clone() const override;
		// Initializes the component
		void Initialize() override;
		// Updates the player move script
		// Params:
		//   dt: The delta time between frames
		void Update(float dt) override;
	};

}

