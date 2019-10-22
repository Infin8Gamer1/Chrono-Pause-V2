/**
	* Author: Jacob Holyfield
	* Project: Chrono-Pause
	* Created: 1/15/2019
**/

// Includes //
#include "stdafx.h"
#include "TestLevel.h"

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
#include "PlayerMove.h"			// PlayerMove

namespace Levels
{
	TestLevel::TestLevel()
		: Level("TestLevel"), mapTileWidth(4), mapTileHeight(6), buttonAnimWidth(2), doorAnimWidth(9)
	{
	}

	void TestLevel::Load()
	{
		// Load the tile map
		tileMap = Tilemap::CreateTilemapFromFile("Assets/Levels/TestLevel.txt");
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

		// Load the hazard
		hazardMesh = CreateQuadMesh(Vector2D(1.0f / 4, 1.0f), Vector2D(0.5f, 0.5f));
		hazardTexture = Texture::CreateTextureFromFile("LAVA.png");
		hazardSpriteSource = new SpriteSource(4, 1, hazardTexture);
		// Make the hazard archetype
		//GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateHazard(hazardMesh, hazardSpriteSource));

		//load the explosion
		explosionMesh = CreateQuadMesh(Vector2D(1.0f / 4, 1.0f / 4), Vector2D(0.5f, 0.5f));
		explosionTexture = Texture::CreateTextureFromFile("TempExpl.png");
		explosionSpriteSource = new SpriteSource(4, 4, explosionTexture);
		GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateExplosion(explosionMesh, explosionSpriteSource));

		// Create the camera controller
		cameraController = new Behaviors::CameraController(Graphics::GetInstance().GetCurrentCamera());
	}

	void TestLevel::Initialize()
	{
		GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateDebugLevelSwaper());

		//create tilemap
		GameObject* map = Archetypes::CreateTilemapObject(mapMesh, mapSpriteSource, tileMap);
		GetSpace()->GetObjectManager().AddObject(*map);

		// Create the hazards
		GameObject* hazard = Archetypes::CreateHazard(hazardMesh, hazardSpriteSource);
		Transform* hazardTransform = static_cast<Transform*>(hazard->GetComponent("Transform"));
		hazardTransform->SetTranslation(ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(8, 4), GetSpace()));
		GetSpace()->GetObjectManager().AddObject(*hazard);

		hazard = Archetypes::CreateHazard(hazardMesh, hazardSpriteSource);
		hazardTransform = static_cast<Transform*>(hazard->GetComponent("Transform"));
		hazardTransform->SetTranslation(ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(3, 5), GetSpace()));
		GetSpace()->GetObjectManager().AddObject(*hazard);

		//create Doors and buttons
        GameObject* door1 = Archetypes::CreateDoor(doorMesh, doorSpriteSource);
        static_cast<Transform*>(door1->GetComponent("Transform"))->SetTranslation(
			ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(9, 6), GetSpace()));

		GetSpace()->GetObjectManager().AddObject(*door1);

        GameObject* button1 = Archetypes::CreateButton(buttonMesh, buttonSpriteSource, door1);
        static_cast<Transform*>(button1->GetComponent("Transform"))->SetTranslation(
			ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(12, 6), GetSpace()));
        
        GetSpace()->GetObjectManager().AddObject(*button1);

		//create player
		GameObject* player = Archetypes::CreatePlayer(playerMesh, playerSpriteSource);
		static_cast<Transform*>(player->GetComponent("Transform"))->SetTranslation(
			ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(14, 6), GetSpace())
		);

		GetSpace()->GetObjectManager().AddObject(*player);

		// Add the player to the camera controller
		static_cast<Behaviors::PlayerMove*>(player->GetComponent("PlayerMove"))->SetCameraController(cameraController);
		cameraController->Retarget(player);
		cameraController->Reset();
		cameraController->SetSpeed(0.005f);

		// Create the clicker object
		GameObject* mouseClicker = Archetypes::CreateClickHelper();
		GetSpace()->GetObjectManager().AddObject(*mouseClicker);
	}

	void TestLevel::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		if (Input::GetInstance().CheckTriggered(VK_F5))
		{
			GetSpace()->RestartLevel();
		}

		// Update the camera controller
		cameraController->Follow();
	}

	void TestLevel::Unload()
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

		//unload the explosion
		delete explosionMesh;
		delete explosionSpriteSource;
		delete explosionTexture;
	}
}