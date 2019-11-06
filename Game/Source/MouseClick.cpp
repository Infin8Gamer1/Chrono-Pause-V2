// -----
// Author: David Wong
// File Name: MouseClick.h
// Project: Chrono Pause
// -----

// Includes
#include <stdafx.h>
#include "MouseClick.h"			// Mouse Click

#include <GameObject.h>			// Game Object
#include <Sprite.h>				// Sprite
#include <Transform.h>			// Transform
#include <Vector2D.h>			// Vector 2D
#include <Input.h>				// Input
#include <Graphics.h>			// Graphics

#include "UIButton.h"			// UI Button

#include <Engine.h>				// Engine
#include <SoundManager.h>		// Sound Manager

// Public Member Functions
namespace Behaviors
{
	// Handle the collisions between the mouse
	void MouseClickCollisionHandler(GameObject& mouseClick, GameObject& other)
	{
		// Save the object we collided with if we let go of the mouse after pressing it
		MouseClick* click = mouseClick.GetComponent<MouseClick>();

		if (Input::GetInstance().IsKeyDown(VK_LBUTTON) && !click->lastClickDown)
		{
			click->selectedObject = &other;
			// Check whether the object has a UI button attached to it
			// If so, then call the button callback function
			UIButton* button = other.GetComponent<UIButton>();
			if (button)
			{
				button->Call();
				return;
			}
			// If not, then keep track of it so we can freeza it lateer
			// Reset the color of the previous object
			if (click->selectedObject != click->freezableObject)
			{
				if (click->freezableSprite)
				{
					click->freezableObject->SetPaused(false);
					click->freezableSprite->SetColor(click->objectOriginalTint);
				}
				click->freezableObject = click->selectedObject;
				click->freezableSprite = click->freezableObject->GetComponent<Sprite>();
				click->objectOriginalTint = click->freezableSprite->GetColor();
				click->freezableSprite->SetColor(click->unfreezeTint);
				click->selectedObject = nullptr;
			}
			else
			{
				click->freezableSprite->SetColor(click->objectOriginalTint);
				click->freezableObject->SetPaused(false);
				click->freezableObject = nullptr;
				click->freezableSprite = nullptr;
				click->selectedObject = nullptr;
			}
		}

		click->lastClickDown = Input::GetInstance().IsKeyDown(VK_LBUTTON);
	}

	MouseClick::MouseClick()
		: Component("MouseClick"), transform(nullptr), freezableObject(nullptr), freezableSprite(nullptr),
		selectedObject(nullptr), objectOriginalTint(), unfreezeTint(1.0f, 0.2f, 0.2f), freezeTint(0.2f, 0.2f, 1.0f), lastClickDown(false)
	{}

	void MouseClick::Initialize()
	{
		// Get the object's transform
		transform = GetOwner()->GetComponent<Transform>();
		// Get the collider and set the collision handle to it
		Collider* collider = GetOwner()->GetComponent<Collider>();
		collider->SetCollisionHandler(MouseClickCollisionHandler);
		Engine::GetInstance().GetModule<SoundManager>()->AddEffect("timepause.wav");
	}

	Component* MouseClick::Clone() const
	{
		return new MouseClick(*this);
	}
	
	void MouseClick::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		// Move the transform around
		Graphics& graphics = Graphics::GetInstance();
		Input& input = Input::GetInstance();
		transform->SetTranslation(graphics.ScreenToWorldPosition(input.GetCursorPosition()));

		// If we have a freezable object selected, then if the space bar is pressed pause/unpause it
		if (freezableObject && Input::GetInstance().CheckTriggered(VK_SPACE))
		{
			freezableObject->SetPaused(!freezableObject->IsPaused());
			freezableSprite->SetColor(freezableObject->IsPaused() ? freezeTint : unfreezeTint);
			if(freezableObject->IsPaused())
				Engine::GetInstance().GetModule<SoundManager>()->PlaySound("timepause.wav");
		}
	}

}