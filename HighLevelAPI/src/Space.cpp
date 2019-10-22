/**
	* Author: David Wong
	* Project: CS230 Lab 3 (Spaces and Levels)
	* File Name: Space.cpp
	* Created: 17 Oct 2018
**/

// Includes //
#include "stdafx.h"
#include "Space.h"

#include "Level.h"

Space::Space(const std::string& name)
	: BetaObject(name), paused(false), currentLevel(nullptr), nextLevel(nullptr), objectManager(this)
{
}

Space::~Space()
{
	Shutdown();
}

void Space::Update(float dt)
{
	// Update the object manager
	objectManager.Update(dt);
	// If there is a next level to go to, then change levels
	if (nextLevel)
	{
		ChangeLevel();
	}

	// Update the current level we are in, as long as level is not paused
	if (currentLevel && !paused)
	{
		currentLevel->Update(dt);
	}
}

void Space::Shutdown()
{
	// Delete the levels that exist
	if (currentLevel)
	{
		currentLevel->Shutdown();
		currentLevel->Unload();
		delete currentLevel;
		currentLevel = nullptr;
	}

	if (nextLevel)
	{
		nextLevel->Shutdown();
		currentLevel->Unload();
		delete nextLevel;
		nextLevel = nullptr;
	}

	objectManager.Shutdown();
	objectManager.Unload();
}

GameObjectManager& Space::GetObjectManager()
{
	return objectManager;
}

bool Space::IsPaused() const
{
	return paused;
}

const std::string& Space::GetLevelName() const
{
	return currentLevel->GetName();
}

void Space::SetPaused(bool paused_)
{
	paused = paused_;
}

void Space::SetLevel(Level* level)
{
	// Set the next level (or the first)
	nextLevel = level;

	// Set the level's parent
	level->SetParent(this);
}

void Space::RestartLevel()
{
	nextLevel = currentLevel;
}

void Space::ChangeLevel()
{
	// If the levels are the same, then just restart the current level
	// otherwise, unload and load the next level
	// However, we always need to shutdown the current level
	// Set the next level, if it is the same, we already kept track of it
	if (currentLevel)
	{
		currentLevel->Shutdown();
		objectManager.Shutdown();
	}

	if (currentLevel != nextLevel)
	{
		if (currentLevel)
		{
			currentLevel->Unload();
			objectManager.Unload();
		}

		nextLevel->Load();
		objectManager.Load();
		delete currentLevel;
	}
	// Set the new states for the levels
	currentLevel = nextLevel;
	nextLevel = nullptr;
	// Initialize the next level/restart the current one
	currentLevel->Initialize();
}