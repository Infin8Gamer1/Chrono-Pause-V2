//------------------------------------------------------------------------------
//
// File Name:	Archetypes.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "UIButton.h"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class GameObject;
class SpriteSource;
class Mesh;
class Tilemap;
class Level;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Archetypes
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	GameObject* CreateText();

	// Create the monkey game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreatePlayer(Mesh* mesh, SpriteSource* spriteSource);

    GameObject* CreateButton(Mesh* mesh, SpriteSource* spritesource, GameObject* door);

	GameObject * CreateButton(Mesh * mesh, SpriteSource* spritesource, std::vector<GameObject*> doors);

    GameObject * CreateDoor(Mesh * mesh, SpriteSource* spritesource);

	GameObject * CreateDoorVertical(Mesh * mesh, SpriteSource* spritesource);
	
	// Create a tilemap object
	// Params:
	//   mesh = The mesh to use for the sprite.
	//   spriteSource = The sprite source to use for the sprite.
	//   map = The map to use for tilemap related components.
	// Returns:
	//   A pointer to the newly constructed game object.
	GameObject* CreateTilemapObject(Mesh* mesh, SpriteSource* spriteSource, Tilemap* map);

	// Create a hazard object
	// Params:
	//   mesh = The mesh to use for the hazard
	//   spriteSource = The spritesource to use for the hazard
	GameObject* CreateHazard(Mesh* mesh, SpriteSource* spriteSource);

	// Create the enemy object
	// Params:
	//   mesh = The mesh to use for the hazard
	//   spriteSource = The Sprite Source for the enemy
	GameObject* CreateEnemy(Mesh* mesh, SpriteSource* spriteSource);

	GameObject* CreateCheckpoint(Mesh* mesh, SpriteSource* spriteSource, Level* level);

	// Creates the click helper
	GameObject* CreateClickHelper();

	// Creates a UI Button
	// Params:
	//   mesh: The mesh used for the button
	//   spriteSource: The sprite source used for the button
	//   callback: The callback used to run the code when pressing the button
	GameObject* CreateUIButton(Mesh* mesh, SpriteSource* spriteSource, Behaviors::UIButtonCallback callback);

	// Creates a helper cube
	// Params:
	//   mesh: The mesh used by the helper cube
	//   spriteSource: The sprite source used by the helper cube
	GameObject* CreateHelperCube(Mesh* mesh, SpriteSource* spriteSource);

	GameObject* CreateDebugLevelSwaper();

	// Creates an explosion object
	// Params:
	//   mesh: The mesh used by the explosion
	//   spriteSource: The sprite source used by the explosion
	GameObject* CreateExplosion(Mesh* mesh, SpriteSource* spriteSource);
}

//----------------------------------------------------------------------------
