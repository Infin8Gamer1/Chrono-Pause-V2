//------------------------------------------------------------------------------
//
// File Name:	TestLevel.h
// Author(s):	Jacob Holyfield
// Project:		Chrono-Pause
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Vector2D.h"
#include "Level.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Texture;
class Mesh;
class SpriteSource;
class GameObject;
class Tilemap;

namespace Behaviors
{
	class CameraController;
}
//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Levels
{
	class TestLevel : public Level
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Creates an instance of Platformer.
		TestLevel();

		// Load the resources associated with Platformer.
		void Load() override;

		// Initialize the memory associated with Platformer.
		void Initialize() override;

		// Update Platformer.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt) override;

		// Unload the resources associated with Platformer.
		void Unload() override;

	private:

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		Mesh* playerMesh;
		SpriteSource* playerSpriteSource;
		Texture* playerTexture;
		const int playerAnimWidth = 3;
		const int playerAnimHeight = 3;

		int mapTileWidth, mapTileHeight;
		Tilemap* tileMap;
		Mesh* mapMesh;
		SpriteSource* mapSpriteSource;
		Texture* mapTexture;

        Mesh* buttonMesh;
        SpriteSource* buttonSpriteSource;
        Texture* buttonTexture;
        const int buttonAnimWidth = 2;

        Mesh* doorMesh;
        SpriteSource* doorSpriteSource;
        Texture* doorTexture;
        const int doorAnimWidth = 9;

		Mesh* explosionMesh;
		SpriteSource* explosionSpriteSource;
		Texture* explosionTexture;

		Mesh* hazardMesh;
		SpriteSource* hazardSpriteSource;
		Texture* hazardTexture;

		Behaviors::CameraController* cameraController;
	};
}

//----------------------------------------------------------------------------
