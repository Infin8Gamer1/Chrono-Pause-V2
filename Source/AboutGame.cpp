// -----
// Author: David Wong, Sage Dupuy
// File Name: AboutGameMenu.cpp
// Project: Chrono Pause
// -----

// Includes
#include <stdafx.h>
#include "AboutGame.h"

#include <MeshHelper.h>			// Mesh Factory
#include <SpriteSource.h>		// Sprite Source
#include <Texture.h>			// Texture
#include <GameObjectManager.h>	// Game Object Manager
#include <GameObject.h>			// Game Object
#include <Space.h>				// Space
#include <Graphics.h>			// Graphics
#include <Mesh.h>				// Mesh
#include <Transform.h>			// Transform
#include <Sprite.h>				// Sprite

#include "Archetypes.h"			// Archetypes
#include "MouseClick.h"			// MouseClick
#include "UIButton.h"			// UI Button
#include "SpriteText.h"
#include <Engine.h>
#include <SoundManager.h>

// Level Includes
#include "MainMenu.h"				// Level 1

// Public Member Functions
namespace Levels
{
	void AboutGameMenuGameButton(Behaviors::UIButton* uiButton)
	{
		uiButton->GetOwner()->GetSpace()->SetLevel(new MainMenu);
	}

	AboutGameMenu::AboutGameMenu()
		: Level("AboutGameMenu"), gameButtonMesh(nullptr), gameButtonSource(nullptr), gameButtonTexture(nullptr)
	{}

	// Loads the level
	void AboutGameMenu::Load()
	{
		// Load the mesh for the button
		gameButtonMesh = CreateQuadMesh(Vector2D(1, 1), Vector2D(0.5f, 0.5f));
		gameButtonTexture = Texture::CreateTextureFromFile("UI pack Space/PNG/glassPanel.png");
		gameButtonSource = new SpriteSource(1, 1, gameButtonTexture);

		// Create the text archetype.
		GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateText());
	}

	// Initializes the level
	void AboutGameMenu::Initialize()
	{


		GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateClickHelper());
		GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateDebugLevelSwaper());

		GameObject* AboutText = new GameObject(*GetSpace()->GetObjectManager().GetArchetypeByName("Text"));
		static_cast<SpriteText*>(AboutText->GetComponent("SpriteText"))->SetText("Chrono-Pause is a puzzle game.\nYour goal is to find the teleporter and get out of there!\n\nWASD are movement controls, E picks stuff up.\n\nYou can click on buttons and doors,\nthen hit space to pause them!\nSpace again will unpause them.");
		static_cast<Transform*>(AboutText->GetComponent("Transform"))->SetTranslation(Vector2D(0, 200));
		GetSpace()->GetObjectManager().AddObject(*AboutText);

		// Create a ui button
		GameObject* uiButton = Archetypes::CreateUIButton(gameButtonMesh, gameButtonSource, AboutGameMenuGameButton);
		static_cast<Transform*>(uiButton->GetComponent("Transform"))->SetTranslation(Vector2D(0, -300));
		GetSpace()->GetObjectManager().AddObject(*uiButton);
		

		GameObject* uiText = new GameObject(*GetSpace()->GetObjectManager().GetArchetypeByName("Text"));
		static_cast<SpriteText*>(uiText->GetComponent("SpriteText"))->SetText("Back To Menu");
		static_cast<Transform*>(uiText->GetComponent("Transform"))->SetTranslation(static_cast<Transform*>(uiButton->GetComponent("Transform"))->GetTranslation());
		GetSpace()->GetObjectManager().AddObject(*uiText);

		//reset the camera translation
		Graphics::GetInstance().GetCurrentCamera().SetTranslation(Vector2D());
	}

	void AboutGameMenu::Unload()
	{
		delete gameButtonSource;
		delete gameButtonTexture;
		delete gameButtonMesh;
	}

}