#pragma once
// -----
// Author: David Wong
// File Name: MouseClick.h
// Project: Chrono Pause
// -----

// Includes 
#include <Component.h>					// Component
#include <ColliderPoint.h>				// Point Collider
#include <Color.h>						// Color

// Forward Declarations
class GameObject;
class Sprite;

namespace Behaviors
{
	// MouseClick Definition
	class MouseClick : public Component
	{
	private:
		// Keep the transform to move the collider around
		Transform* transform;
		// Keep track of the object we selected to freeze and unfreeze
		GameObject* freezableObject;
		Sprite* freezableSprite;
		Color objectOriginalTint;
		// The colors of when the object is selected or frozen
		Color unfreezeTint, freezeTint;
		// Keep track of the objects we selected
		GameObject* selectedObject;
		// Keeps track when the mouse button is down or up
		bool lastClickDown;
		// Handles the click events
		// Params:
		//   mouseClick: The object used for the mouse clicks
		//   other: The other object we collided with
		friend void MouseClickCollisionHandler(GameObject& mouseClick, GameObject& other);
	public:
		// Default Constructor
		MouseClick();
		// Initializes the component
		void Initialize() override;
		// Clones the component
		Component* Clone() const override;
		// Updates the component
		// Params:
		//   dt: The delta time between frames
		void Update(float dt);
	};
}