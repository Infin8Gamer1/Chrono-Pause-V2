// -----
// Author: David Wong
// File Name: ExplosionTimer.cpp
// Project: Chrono Pause
// -----

// Includes
#include <stdafx.h>
#include "ExplosionTimer.h"

#include <Space.h>			// Space
#include <GameObject.h>		// Game Object
#include <Animation.h>		// Animation
#include <Engine.h>
#include <SoundManager.h>


namespace Behaviors
{
	ExplosionTimer::ExplosionTimer(bool reset_)
		: Component("ExplosionTimer"), reset(reset_), exploding(false), animationStarted(false), animation(nullptr)
	{
	}

	ExplosionTimer* ExplosionTimer::Clone() const
	{
		return new ExplosionTimer(*this);
	}

	void ExplosionTimer::Initialize()
	{
		animation = static_cast<Animation*>(GetOwner()->GetComponent("Animation"));
		Engine::GetInstance().GetModule<SoundManager>()->AddEffect("explosion.wav");
	}

	void ExplosionTimer::Explode() {
		exploding = true;
		Engine::GetInstance().GetModule<SoundManager>()->PlaySound("explosion.wav");
	}

	void ExplosionTimer::Update(float dt)
	{

		if (exploding) {
			if (!animationStarted) {
				animation->Play(0, 16, 0.05f, false);
				animationStarted = true;
			} else if (!animation->IsRunning()) {
				if (reset)
					GetOwner()->GetSpace()->RestartLevel();

				GetOwner()->Destroy();
			}
		}
	}

	void ExplosionTimer::SetResetLevel(bool reset_)
	{
		reset = reset_;
	}
}