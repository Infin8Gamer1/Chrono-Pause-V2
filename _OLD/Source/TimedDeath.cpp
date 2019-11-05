// -----
// Author: David Wong
// Project: CS230 Lab 2
// File Name: TimedDeath.cpp
// -----

// Includes
#include "stdafx.h"
#include "TimedDeath.h"			// Timed Death

#include "GameObject.h"			// Game Object

namespace Behaviors
{

	TimedDeath::TimedDeath(float timeUntilDeath)
		: Component("TimedDeath"), timeUntilDeath(timeUntilDeath)
	{
	}

	Component* TimedDeath::Clone() const
	{
		return new TimedDeath(*this);
	}

	void TimedDeath::Update(float dt)
	{
		timeUntilDeath -= dt;
		if (timeUntilDeath <= 0)
		{
			GetOwner()->Destroy();
		}
	}
}