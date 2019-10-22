/**
* Author: David Wong
* Project: CS230 Lab 6
* File Name: ColorChange.cpp
**/

// Includes //
#include "stdafx.h"
#include "ColorChange.h"

#include "GameObject.h"			// Game Object
#include "Sprite.h"				// Sprite

#include "Collider.h"			// Collider

// Public Member Functions //
namespace Behaviors
{
	void ColorChangeCollisionHandler(GameObject& object, GameObject& other);

	ColorChange::ColorChange(const Color& normalColor, const Color& collidedColor, float collidedColorTime)
		: Component("ColorChange"), normalColor(normalColor), collidedColor(collidedColor), collidedColorTime(collidedColorTime), timer(0.0f),
		sprite(nullptr), collided(false)
	{

	}

	Component* ColorChange::Clone() const
	{
		return new ColorChange(*this);
	}

	void ColorChange::Initialize()
	{
		sprite = static_cast<Sprite*>(this->GetOwner()->GetComponent("Sprite"));
		// Set the collision handler
		Collider* collider = reinterpret_cast<Collider*>(GetOwner()->GetComponent("Collider"));
		collider->SetCollisionHandler(Behaviors::ColorChangeCollisionHandler);
	}

	void ColorChange::Update(float dt)
	{
		timer -= dt;
		if (collided)
		{
			timer = collidedColorTime;
			collided = false;
			sprite->SetColor(collidedColor);
		}
		else if (timer <= 0.0f)
		{
			sprite->SetColor(normalColor);
		}
	}

	void ColorChangeCollisionHandler(GameObject& object, GameObject& other)
	{
		UNREFERENCED_PARAMETER(other);
		ColorChange* objectColorChange = reinterpret_cast<ColorChange*>(object.GetComponent("ColorChange"));
		objectColorChange->collided = true;
	}
}