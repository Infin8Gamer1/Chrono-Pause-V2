// -----
// Author: David Wong, Sage Dupuy
// File Name: MainMenu.cpp
// Project: Chrono Pause
// -----

// Includes
#include <stdafx.h>
#include "MainMenu.h"

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
#include "Level1.h"				// Level 1
#include "AboutGame.h"

// Public Member Functions
namespace Levels
{
	void MainMenuGameButton(Behaviors::UIButton* uiButton)
	{
		uiButton->GetOwner()->GetSpace()->SetLevel(new Level1);
	}

	void AboutGameGameButton(Behaviors::UIButton* uiButton)
	{
		uiButton->GetOwner()->GetSpace()->SetLevel(new AboutGameMenu);
	}

	void QuitGameGameButton(Behaviors::UIButton* uiButton)
	{
		Engine::GetInstance().Stop();
	}

	MainMenu::MainMenu()
		: Level("MainMenu"), gameButtonMesh(nullptr), gameButtonSource(nullptr), gameButtonTexture(nullptr)
	{}

	// Loads the level
	void MainMenu::Load()
	{
		// Load the mesh for the button
		gameButtonMesh = CreateQuadMesh(Vector2D(1, 1), Vector2D(0.5f, 0.5f));
		gameButtonTexture = Texture::CreateTextureFromFile("UI pack Space/PNG/glassPanel.png");
		gameButtonSource = new SpriteSource(1, 1, gameButtonTexture);

		titleMesh = CreateQuadMesh(Vector2D(1, 1), Vector2D(0.5f, 0.5f));
		titleTexture = Texture::CreateTextureFromFile("TitleScreen.png");
		titleSource = new SpriteSource(1, 1, titleTexture);

		// Create the text archetype.
		GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateText());
	}

	// Initializes the level
	void MainMenu::Initialize()
	{
		//set full screen
		Graphics::GetInstance().SetFullScreen(true);

		// Create the title
		GameObject*	title = new GameObject("Title");
		Transform* titleTransform = new Transform(Vector2D(0, 200), Vector2D(128*5, 32 * 5));
		Sprite* sprite = new Sprite;
		sprite->SetMesh(titleMesh);
		sprite->SetSpriteSource(titleSource);
		title->AddComponent(titleTransform);
		title->AddComponent(sprite);
		GetSpace()->GetObjectManager().AddObject(*title);


		GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateClickHelper());
		GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateDebugLevelSwaper());

		// Create a ui button for start game
		GameObject* uiButton = Archetypes::CreateUIButton(gameButtonMesh, gameButtonSource, MainMenuGameButton);
		GetSpace()->GetObjectManager().AddObject(*uiButton);
		

		GameObject* uiText = new GameObject(*GetSpace()->GetObjectManager().GetArchetypeByName("Text"));
		static_cast<SpriteText*>(uiText->GetComponent("SpriteText"))->SetText("Start Game");
		static_cast<Transform*>(uiText->GetComponent("Transform"))->SetTranslation(static_cast<Transform*>(uiButton->GetComponent("Transform"))->GetTranslation());
		GetSpace()->GetObjectManager().AddObject(*uiText);

		// Create a ui button for about menu
		GameObject* uiButton2 = Archetypes::CreateUIButton(gameButtonMesh, gameButtonSource, AboutGameGameButton);
		static_cast<Transform*>(uiButton2->GetComponent("Transform"))->SetTranslation(Vector2D(0, -100));
		GetSpace()->GetObjectManager().AddObject(*uiButton2);


		GameObject* uiText2 = new GameObject(*GetSpace()->GetObjectManager().GetArchetypeByName("Text"));
		static_cast<SpriteText*>(uiText2->GetComponent("SpriteText"))->SetText("About Game");
		static_cast<Transform*>(uiText2->GetComponent("Transform"))->SetTranslation(static_cast<Transform*>(uiButton2->GetComponent("Transform"))->GetTranslation());
		GetSpace()->GetObjectManager().AddObject(*uiText2);

		// Create a ui button for about menu
		GameObject* uiButton3 = Archetypes::CreateUIButton(gameButtonMesh, gameButtonSource, QuitGameGameButton);
		static_cast<Transform*>(uiButton3->GetComponent("Transform"))->SetTranslation(Vector2D(0, -200));
		GetSpace()->GetObjectManager().AddObject(*uiButton3);


		GameObject* uiText3 = new GameObject(*GetSpace()->GetObjectManager().GetArchetypeByName("Text"));
		static_cast<SpriteText*>(uiText3->GetComponent("SpriteText"))->SetText("Quit Game");
		static_cast<Transform*>(uiText3->GetComponent("Transform"))->SetTranslation(static_cast<Transform*>(uiButton3->GetComponent("Transform"))->GetTranslation());
		GetSpace()->GetObjectManager().AddObject(*uiText3);


		//reset the camera translation
		Graphics::GetInstance().GetCurrentCamera().SetTranslation(Vector2D());
	}

	void MainMenu::Unload()
	{
		delete titleSource;
		delete titleTexture;
		delete titleMesh;

		delete gameButtonSource;
		delete gameButtonTexture;
		delete gameButtonMesh;
	}

}