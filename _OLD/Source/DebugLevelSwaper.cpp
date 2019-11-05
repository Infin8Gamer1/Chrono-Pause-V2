//------------------------------------------------------------------------------
//
// File Name:	DebugLevelSwaper.cpp
// Author(s):	Jacob Holyfield (jacob.holyfield)
// Project:		Chrono-Pause
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include <stdafx.h>
#include "DebugLevelSwaper.h"
#include <Space.h>
#include <Input.h>
#include "MainMenu.h"
#include "Level1.h"
#include "Level2.h"
#include "TestLevel.h"

DebugLevelSwaper::DebugLevelSwaper() : Component("DebugLevelSwaper")
{
}

Component * DebugLevelSwaper::Clone() const
{
    return new DebugLevelSwaper(*this);
}

void DebugLevelSwaper::Initialize()
{
    
}

void DebugLevelSwaper::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

#if _DEBUG
	static const Input& input = Input::GetInstance();

	if (input.CheckReleased('1'))
	{
		GetOwner()->GetSpace()->SetLevel(new Levels::Level1());
	} else if (input.CheckReleased('2'))
	{
		GetOwner()->GetSpace()->SetLevel(new Levels::Level2());
	} else if (input.CheckReleased('3'))
	{
		GetOwner()->GetSpace()->SetLevel(new Levels::TestLevel());
	} else if (input.CheckReleased('0'))
	{
		GetOwner()->GetSpace()->SetLevel(new Levels::MainMenu());
	}
#endif
}


