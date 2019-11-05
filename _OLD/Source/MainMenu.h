	#pragma once
// -----
// Author: David Wong
// File Name: MainMenu.h
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
	void MainMenuGameButton(Behaviors::UIButton* uiButton);
	void AboutGameGameButton(Behaviors::UIButton* uiButton);
	void QuitGameGameButton(Behaviors::UIButton* uiButton);

	class MainMenu : public Level
	{
	private:
		// Assets for the button that sends you to the main game
		Mesh* gameButtonMesh;
		SpriteSource* gameButtonSource;
		Texture* gameButtonTexture;

		// Assets forr the title screen
		Mesh* titleMesh;
		SpriteSource* titleSource;
		Texture* titleTexture;
	public:
		// Constructor for MainMenu
		MainMenu();
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