//------------------------------------------------------------------------------
//
// File Name:	ColorChange.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h" // base class
#include <Color.h>	 // Color
#include <Vector2D.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Sprite;
class Physics;
struct MapCollision;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{
	enum InnerStates
	{
		InnerStateEnter,
		InnerStateUpdate,
		InnerStateExit
	};

	class Enemy : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		Enemy();

		// Return a new copy of the component.
		Component* Clone() const;

		// Initialize data for this object.
		void Initialize();

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		void Update(float dt) override;

		// Map collision handler for Monkey objects.
		// Params:
		//   object = The monkey object.
		//   collision = Which sides the monkey collided on.
		friend void EnemyMapCollisionHandler(GameObject& object,
			const MapCollision& collision);

		// Sets the next state of the enemy.
		// Params:
		//   nextState = The next state the enemy should be in.
		void SetState(unsigned nextState);

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		unsigned currentState;  // The current state of the enemy. Ex: idle, wander, chase
		unsigned nextState;		// The next state of the enemy.

		unsigned innerState; // The inner state of the current state. Ex: enter, update, exit
		
		float timer; // Used for delaying state changes, etc.
		float stateChangeTime; // Amount of time to wait before changing states.

		GameObject* player;  // The player we want to chase after
		Physics*	physics; // The enemy physics
		int wanderDirection;  // The wander direction
		float wanderSpeed; // The wandering speed
		Vector2D gravity;  // Gravity
	};
}
