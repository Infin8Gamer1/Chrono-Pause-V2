//------------------------------------------------------------------------------
//
// File Name:	Level.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <BetaObject.h>
#include <Vector2D.h>
#include <Serializable.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Space;
class GameObject;
class Tilemap;
class CameraController;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface (functions) declared in the header.
class Level : public BetaObject, public Serializable
{
public:
	// Creates a game state.
	// Params:
	//   name = Name to use for this state.
	Level(const std::string& name);

	// Retrieve the space in which the level is running.
	Space* GetSpace() const;

	// Loads object data from a file.
	void Deserialize(Parser& parser) override;

	// Saves object data to a file.
	void Serialize(Parser& parser) const override;

	void SaveLevel();

	void LoadLevel(bool createTewakBars = false);

	void SetFileLocation(std::string fileLocation);

	std::string GetFileLocation();

	CameraController* cameraController;

private:

	void DisplayMessage(std::string what);

	std::string fileLocation;

	bool createTweakBarsOnLoad;
};

//------------------------------------------------------------------------------
