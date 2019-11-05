// -----
// Author: David Wong
// File Name: UIButton.cpp
// Project: Chrono Pause
// -----

// Includes
#include <stdafx.h>
#include "UIButton.h"			// UI Buttons
#include <Engine.h>				// Engine
#include <SoundManager.h>		// Sound Managerr

// Public Member Functions
namespace Behaviors
{
	UIButton::UIButton(UIButtonCallback callback_)
		: Component("UIButton"), callback(callback_)
	{

	}

	Component* UIButton::Clone() const
	{
		return new UIButton(*this);
	}

	void UIButton::Initialize()
	{
		Engine::GetInstance().GetModule<SoundManager>()->AddEffect("button.wav");
	}

	void UIButton::Call()
	{
		if (callback)
		{
			callback(this);
			Engine::GetInstance().GetModule<SoundManager>()->PlaySound("button.wav");
		}
	}

	void UIButton::SetButtonCallback(UIButtonCallback callback_)
	{
		callback = callback_;
	}
}