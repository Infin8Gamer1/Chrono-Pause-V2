//------------------------------------------------------------------------------
//
// File Name:	Lava.cpp
// Author(s):	Jacob Holyfield
// Project:		Chrono pause V2
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Lava.h"

#include <GameObject.h>		// Game Object
#include <Animation.h>		// Animation

namespace Behaviors
{

	Behaviors::Lava::Lava() : Component("Lava"), animation(nullptr)
	{
	}

	Lava* Behaviors::Lava::Clone() const
	{
		return new Lava(*this);
	}

	void Lava::Initialize()
	{
		animation = GetOwner()->GetComponent<Animation>();

		animation->Play(0.2f, true);
	}

	void Lava::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
	}

}