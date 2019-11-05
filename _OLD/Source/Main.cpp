//------------------------------------------------------------------------------
//
// File Name:	Main.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

// BetaFramework Engine
#include <Engine.h>

// Engine modules
#include "Space.h"
#include "SoundManager.h"

// Initial game state
#include "MainMenu.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Main function
int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR command_line, _In_ int show)
{
	// Enable memory leak checking
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	// Unused parameters
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(command_line);
	UNREFERENCED_PARAMETER(show);
	UNREFERENCED_PARAMETER(instance);

	// Create a new space called "GameSpace"
	Space* space = new Space("GameSpace");

	// Set initial level to the second level.
	space->SetLevel(new Levels::MainMenu);

	// Add additional modules to engine
	Engine::GetInstance().AddModule(space);
	Engine::GetInstance().AddModule(new SoundManager());

	//load audio
	SoundManager* soundManager = Engine::GetInstance().GetModule<SoundManager>();
	soundManager->AddMusic("chronoPause_bgm_01_jkings.mp3");
	soundManager->AddEffect("teleport.wav");
	/*soundManager->AddEffect("Cool_sound.wav");
	soundManager->AddEffect("End_Goal.wav");
	soundManager->AddEffect("explosion.wav");
	soundManager->AddEffect("Time_Toggle_Sound.wav");
	soundManager->AddEffect("Jump.wav");*/

	FMOD::Channel* musicChanel = soundManager->PlaySound("chronoPause_bgm_01_jkings.mp3");

	

	// Game engine goes!
	Engine::GetInstance().Start(1920, 1080, 200);

	

	return 0;
}
