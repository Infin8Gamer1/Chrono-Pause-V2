/**
	* Author: Jacob Holyfield
	* Project: Chrono-Pause
	* Created: 1/15/2019
**/

// Includes //
#include "stdafx.h"
#include "Level1.h"

#include <Engine.h>				// Engine
#include <Mesh.h>				// Mesh
#include <Texture.h>			// Texture
#include <Input.h>				// Input
#include <Graphics.h>			// Graphics (To get the camera)
#include <ColliderTilemap.h>	// Collider Tilemap

#include "Archetypes.h"			// Archetypes
#include "MeshHelper.h"			// Mesh Helper
#include "SpriteSource.h"		// Sprite Source
#include "Transform.h"			// Transform
#include "Tilemap.h"			// Tile Map
#include "Space.h"				// Space
#include "CameraController.h"	// Camera Controller
#include "PlayerMove.h"			// Player Move
#include "Level2.h"

#include "MainMenu.h"			// Main Menu

namespace Levels
{
	Level1::Level1()
		: Level("Level1"), mapTileWidth(4), mapTileHeight(6)
	{
	}

	void Level1::Load()
	{
		// Load the tile map
		tileMap = Tilemap::CreateTilemapFromFile("Assets/Levels/Level1.txt");
		if (!tileMap)
		{
			std::cerr << "[ERROR]: Tilemap doesn't exist" << std::endl;
		}

		mapMesh = CreateQuadMesh(Vector2D(1.0f / mapTileWidth, 1.0f / mapTileHeight), Vector2D(0.5f, 0.5f));
		mapTexture = Texture::CreateTextureFromFile("TileMap (2).png");
		mapSpriteSource = new SpriteSource(mapTileWidth, mapTileHeight, mapTexture);

		// Load the player
		playerMesh = CreateQuadMesh(Vector2D(1.0f / static_cast<float>(playerAnimWidth), 1.0f / static_cast<float>(playerAnimHeight)), 
			Vector2D(0.5f, 0.5f));

		playerTexture = Texture::CreateTextureFromFile("player.png");
		playerSpriteSource = new SpriteSource(playerAnimWidth, playerAnimHeight, playerTexture);

		//load button
        buttonMesh = CreateQuadMesh(Vector2D(1.0f / buttonAnimWidth, 1.0f), Vector2D(0.5f, 0.5f));
        buttonTexture = Texture::CreateTextureFromFile("BUTTON.png");
        buttonSpriteSource = new SpriteSource(buttonAnimWidth, 1, buttonTexture);

		//load doors
        doorMesh = CreateQuadMesh(Vector2D(1.0f / doorAnimWidth, 1.0f), Vector2D(0.5f, 0.5f));
        doorTexture = Texture::CreateTextureFromFile("DOOR.png");
        doorSpriteSource = new SpriteSource(doorAnimWidth, 1, doorTexture);

		// Load the checkpoint
		checkpointMesh = CreateQuadMesh(Vector2D(1.0f / checkpointAnimWidth, 1.0f / checkpointAnimHeight), Vector2D(0.5f, 0.5f));
		checkpointTexture = Texture::CreateTextureFromFile("TELEPORT.png");
		checkpointSpriteSource = new SpriteSource(checkpointAnimWidth, checkpointAnimHeight, checkpointTexture);

		// Load the hazard
		hazardMesh = CreateQuadMesh(Vector2D(1.0f / 4, 1.0f), Vector2D(0.5f, 0.5f));
		hazardTexture = Texture::CreateTextureFromFile("LAVA.png");
		hazardSpriteSource = new SpriteSource(4, 1, hazardTexture);

		// Create the camera controller
		cameraController = new Behaviors::CameraController(Graphics::GetInstance().GetCurrentCamera());
	}

	void Level1::Initialize()
	{
		GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateDebugLevelSwaper());
		
		//create tilemap
		GameObject* map = Archetypes::CreateTilemapObject(mapMesh, mapSpriteSource, tileMap);
		GetSpace()->GetObjectManager().AddObject(*map);

		//create Doors and buttons
        GameObject* door1 = Archetypes::CreateDoor(doorMesh, doorSpriteSource);
        static_cast<Transform*>(door1->GetComponent("Transform"))->SetTranslation(
			ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(4, 1), GetSpace()));

		GetSpace()->GetObjectManager().AddObject(*door1);

        GameObject* button1 = Archetypes::CreateButton(buttonMesh, buttonSpriteSource, door1);
        static_cast<Transform*>(button1->GetComponent("Transform"))->SetTranslation(
			ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(2, 1), GetSpace()));
        
        GetSpace()->GetObjectManager().AddObject(*button1);

		GameObject* door2 = Archetypes::CreateDoor(doorMesh, doorSpriteSource);
		static_cast<Transform*>(door2->GetComponent("Transform"))->SetTranslation(
			ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(6, 8), GetSpace()));

		GetSpace()->GetObjectManager().AddObject(*door2);

		GameObject* button2 = Archetypes::CreateButton(buttonMesh, buttonSpriteSource, door2);
		static_cast<Transform*>(button2->GetComponent("Transform"))->SetTranslation(
			ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(19, 4), GetSpace()));

		GetSpace()->GetObjectManager().AddObject(*button2);
		
		//create player
		GameObject* player = Archetypes::CreatePlayer(playerMesh, playerSpriteSource);
		static_cast<Transform*>(player->GetComponent("Transform"))->SetTranslation(
			ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(1, 1), GetSpace())
		);
		static_cast<Behaviors::PlayerMove*>(player->GetComponent("PlayerMove"))->SetCameraController(cameraController);
		GetSpace()->GetObjectManager().AddObject(*player);

		// Add the player to the camera controller
		cameraController->Retarget(player);
		cameraController->Reset();
		cameraController->SetSpeed(0.01f);

		// End Goal
		GameObject* endGoal = Archetypes::CreateCheckpoint(checkpointMesh, checkpointSpriteSource, new Level2());
		static_cast<Transform*>(endGoal->GetComponent("Transform"))->SetTranslation(
			ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(4, 8), GetSpace()) + Vector2D(0, -17.0f)
		);
		GetSpace()->GetObjectManager().AddObject(*endGoal);

		// Create the clicker object
		GameObject* mouseClicker = Archetypes::CreateClickHelper();
		GetSpace()->GetObjectManager().AddObject(*mouseClicker);
	}

	void Level1::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		if (Input::GetInstance().CheckTriggered(VK_F5))
		{
			GetSpace()->RestartLevel();
		}
		else if (Input::GetInstance().CheckTriggered(VK_F1))
		{
			GetSpace()->SetLevel(new MainMenu);
		}

		// Update the camera controller
		cameraController->Follow();
	}

	void Level1::Unload()
	{
		// Unload the camera controller
		delete cameraController;

		// Unlaod the hazard
		delete hazardSpriteSource;
		delete hazardTexture;
		delete hazardMesh;

		// Unload the player 
		delete playerSpriteSource;
		delete playerTexture;
		delete playerMesh;

		//unload button
        delete buttonSpriteSource;
        delete buttonTexture;
        delete buttonMesh;

		//unload door
        delete doorSpriteSource;
        delete doorTexture;
        delete doorMesh;

		// Unload the tile map
		delete mapSpriteSource;
		delete mapTexture;
		delete mapMesh;
		delete tileMap;

		//unload checkpoint
		delete checkpointMesh;
		delete checkpointSpriteSource;
		delete checkpointTexture;
	}
}