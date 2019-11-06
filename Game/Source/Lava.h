//------------------------------------------------------------------------------
//
// File Name:	Lava.h
// Author(s):	Jacob Holyfield
// Project:		Chrono pause V2
//
//------------------------------------------------------------------------------

#pragma once
// Include
#include <Component.h>


class Animation;

namespace Behaviors
{
	class Lava : public Component
	{
	private:
		//animation component
		Animation* animation;

	public:
		// Constructor
		// Params:
		//   duration: How long the explosion lasts
		Lava();
		// Clones the component
		Lava* Clone() const override;
		// Initializes the component
		void Initialize() override;
		// Updates the component
		// Params:
		//   dt: The time between frames
		void Update(float dt) override;
	};
}