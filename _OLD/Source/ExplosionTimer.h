#pragma once
// -----
// Author: David Wong
// File Name: ExplosionTimer
// Project: Chrono Pause
// -----

// Include
#include <Component.h>


class Animation;

namespace Behaviors
{
	class ExplosionTimer : public Component
	{
	private:
		//if we are exploding
		bool exploding;
		// Whether the explosion resets the level after the explosion
		bool reset;
		// has the animation started yet?
		bool animationStarted;
		//animation component
		Animation* animation;

	public:
		// Constructor
		// Params:
		//   duration: How long the explosion lasts
		ExplosionTimer(bool reset_ = true);
		// Clones the component
		ExplosionTimer* Clone() const override;
		// Initializes the component
		void Initialize() override;
		//call to explode.exe
		void Explode();
		// Updates the component
		// Params:
		//   dt: The time between frames
		void Update(float dt) override;
		// Sets whether the explosion resets the level
		// Params:
		//   reset_: Whether the explosion resets the level
		void SetResetLevel(bool reset_);
	};
}