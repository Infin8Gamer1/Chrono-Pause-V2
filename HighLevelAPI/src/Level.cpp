/**
* Author: David Wong
* Project: CS230 Lab 3 (Spaces and Levels)
* File Name: Level.cpp
* Created: 17 Oct 2018
**/

// Includes //
#include "stdafx.h"
#include "Level.h"
#include "Space.h"

Level::Level(const std::string& name)
	: BetaObject(name)
{

}

// Returns the level's space
Space* Level::GetSpace() const
{
	return static_cast<Space*>(GetParent());
}