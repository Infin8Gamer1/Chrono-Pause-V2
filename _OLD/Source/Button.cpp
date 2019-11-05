//------------------------------------------------------------------------------
//
// File Name:	Button.cpp
// Author(s):	Sage Dupuy (sage.dupuy), Jacob Holyfield (jacob.holyfield)
// Project:		Chrono-Pause
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include <stdafx.h>
#include "Button.h"					// Button
#include <GameObject.h>				// Game Object
#include <Collider.h>				// Collider
#include <Sprite.h>					// Sprite
#include "Door.h"					// Door

void ButtonObjectCollisionHandler(GameObject & current, GameObject & other)
{
	if (other.GetName() == "Player" || other.GetName() == "HelperCube")
	{
		static_cast<Button*>(current.GetComponent("Button"))->Pressed = true;
	}
}

Button::Button(GameObject * _door) : Component("Button")
{
	doors.push_back(_door);
	collider = nullptr;
	Pressed = false;
	sprite = nullptr;
}

Button::Button(std::vector<GameObject*> _doors) : Component("Button")
{
	doors = _doors;
	collider = nullptr;
	Pressed = false;
	sprite = nullptr;
}

Component * Button::Clone() const
{
    return new Button(*this);
}

void Button::Initialize()
{
    sprite = static_cast<Sprite*>(GetOwner()->GetComponent("Sprite"));
    collider = static_cast<Collider*>(GetOwner()->GetComponent("Collider"));
    collider->SetCollisionHandler(ButtonObjectCollisionHandler);
}

void Button::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

    if(Pressed)
    {
		for (size_t i = 0; i < doors.size(); i++)
		{
			static_cast<Door*>(doors.at(i)->GetComponent("Door"))->open = true;
		}
        
		sprite->SetFrame(1);
    }
    else
    {
		for (size_t i = 0; i < doors.size(); i++)
		{
			static_cast<Door*>(doors.at(i)->GetComponent("Door"))->open = false;
		}

        sprite->SetFrame(0);
    }

    Pressed = false;
}
