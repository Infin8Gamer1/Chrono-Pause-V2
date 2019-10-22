	#pragma once
// -----
// Author: David Wong
// File Name: AboutGameMenu.h
// Project: Chrono Pause
// -----

// Includes
#include <Level.h>			// Level

// Forward Declarations
class Mesh;
class SpriteSource;
class Texture;
namespace Behaviors
{
	class UIButton;
	class MouseClick;
}

namespace Levels
{
	// Forward Declarations
	void AboutGameMenuGameButton(Behaviors::UIButton* uiButton);

	class AboutGameMenu : public Level
	{
	private:
		// Assets for the button that sends you to the main game
		Mesh* gameButtonMesh;
		SpriteSource* gameButtonSource;
		Texture* gameButtonTexture;
	public:
		// Constructor for AboutGameMenu
		AboutGameMenu();
		// Loads the level
		void Load() override;
		// Initializes the level
		void Initialize() override;
		// Updates the level
		//void Update(float dt) override;
		// Unloads the level
		void Unload() override;
	};
}