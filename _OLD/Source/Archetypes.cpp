/**
* Author: David Wong, Sage Dupuy
* Project: CS230 Project 2 (Game Object and Game Manager)
* File Name: Archetypes.cpp
* Created: 17 Oct 2018
**/

// Includes //
#include "stdafx.h"
#include "Archetypes.h"

#include <Mesh.h>					// Mesh
#include <Texture.h>				// Texture
									
#include "GameObject.h"				// Game Object
#include <Physics.h>				// Physics
#include "Transform.h"				// Transform
#include "Animation.h"				// Animation
#include "Sprite.h"					// Sprite
#include "SpriteTilemap.h"			// Sprite Tilemap
#include "SpriteSource.h"			// Sprite Source
#include "ColliderCircle.h"			// Circle Collider
#include "ColliderRectangle.h"		// Rectangle Collider
#include "ColliderPoint.h"			// Point Collider
#include "ColliderTilemap.h"		// Tilemap Collider
									
#include "Enemy.h"					// Enemy
#include "ColorChange.h"			// Color Change
#include "PlayerMove.h"				// Player Move
#include "TimedDeath.h"				// TimedDeath
#include "PlayerAnimController.h"	// Player Animation Controller
#include "Button.h"					// Button
#include "Door.h"                   // Door
#include "MouseClick.h"				// Mouse Click
#include <Level.h>					// Level
#include "LevelChanger.h"			// Level Changer
#include "SpriteText.h"				// Sprite Text
#include "DebugLevelSwaper.h"		// Debug Level Swaper
#include "ExplosionTimer.h"			// Explosion Timer

#include <Graphics.h>

namespace Archetypes
{
	// Public Functions //

	// Create a text game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object.
	GameObject* CreateText()
	{
		// Create a new game object.
		GameObject* text = new GameObject("Text");

		// Create a new transform.
		Transform* transform = new Transform(0.0f, 0.0f);
		transform->SetScale(Vector2D(64.0f, 64.0f));
		text->AddComponent(transform);

		// Create a new sprite text.
		SpriteText* spriteText = new SpriteText();
		spriteText->SetHorizontalAlignment(SpriteText::Alignment::CENTER);
		spriteText->SetVerticalAlignment(SpriteText::Alignment::CENTER);
		text->AddComponent(spriteText);

		return text;
	}

	GameObject* CreatePlayer(Mesh* mesh, SpriteSource* source)
	{
		GameObject* monkey = new GameObject("Player");
		Sprite* sprite = new Sprite;

		sprite->SetSpriteSource(source);
		sprite->SetMesh(mesh);

		monkey->AddComponent(new Transform(Vector2D(), Vector2D(100, 100)));
		monkey->AddComponent(sprite);
		monkey->AddComponent(new Physics);
		monkey->AddComponent(new Animation);
		monkey->AddComponent(new Behaviors::PlayerAnimController);
		monkey->AddComponent(new ColliderRectangle(Vector2D(48.0f, 50.0f)));
		monkey->AddComponent(new Behaviors::PlayerMove);

		return monkey;
	}

    GameObject * CreateButton(Mesh * mesh, SpriteSource* spritesource, GameObject* door)
    {
        GameObject* button = new GameObject("Button");
        Sprite* sprite = new Sprite;

        sprite->SetSpriteSource(spritesource);
        sprite->SetMesh(mesh);

        button->AddComponent(new Transform(Vector2D(), Vector2D(100.0f, 100.0f)));
        button->AddComponent(sprite);
        button->AddComponent(new ColliderRectangle(Vector2D(50.0f, 10.0f), Vector2D(0, -40.0f)));
        button->AddComponent(new Button(door));

        return button;
    }

	GameObject * CreateButton(Mesh * mesh, SpriteSource* spritesource, std::vector<GameObject*> doors)
	{
		GameObject* button = new GameObject("Button");
		Sprite* sprite = new Sprite;

		sprite->SetSpriteSource(spritesource);
		sprite->SetMesh(mesh);

		button->AddComponent(new Transform(Vector2D(), Vector2D(100.0f, 100.0f)));
		button->AddComponent(sprite);
		button->AddComponent(new ColliderRectangle(Vector2D(50.0f, 10.0f), Vector2D(0, -40.0f)));
		button->AddComponent(new Button(doors));

		return button;
	}

    GameObject * CreateDoor(Mesh * mesh, SpriteSource* spritesource)
    {
        GameObject* door = new GameObject("Door");
        Sprite* sprite = new Sprite;

        sprite->SetSpriteSource(spritesource);
        sprite->SetMesh(mesh);

        door->AddComponent(new Transform(Vector2D(), Vector2D(75.0f, 100.0f)));
        door->AddComponent(sprite);
        door->AddComponent(new Animation);
        door->AddComponent(new ColliderRectangle(Vector2D(50.0f, 50.0f)));
        door->AddComponent(new Door());

        return door;
    }

	GameObject * CreateDoorVertical(Mesh * mesh, SpriteSource* spritesource)
	{
		GameObject* door = new GameObject("Door");
		Sprite* sprite = new Sprite;

		sprite->SetSpriteSource(spritesource);
		sprite->SetMesh(mesh);

		door->AddComponent(new Transform(Vector2D(), Vector2D(75.0f, 100.0f),  static_cast<float>(M_PI/180 * 90.0f)));
		door->AddComponent(sprite);
		door->AddComponent(new Animation);
		door->AddComponent(new ColliderRectangle(Vector2D(50.0f, 50.0f)));
		door->AddComponent(new Door(Door::DoorType::Vertical));

		return door;
	}

	GameObject* CreateTilemapObject(Mesh* mesh, SpriteSource* spriteSource, Tilemap* map)
	{
		GameObject* tileMap = new GameObject("Tilemap");

		Vector2D scale = Vector2D(100, 100);
		Transform* transform = new Transform(Vector2D(0, 0), scale, 0.0f);

		SpriteTilemap* sprite = new SpriteTilemap;
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);
		sprite->SetTilemap(map);

		ColliderTilemap* collider = new ColliderTilemap;
		collider->SetTilemap(map);

		tileMap->AddComponent(transform);
		tileMap->AddComponent(sprite);
		tileMap->AddComponent(collider);

		return tileMap;
	}

	GameObject* CreateHazard(Mesh* mesh, SpriteSource* spriteSource)
	{
		GameObject* hazard = new GameObject("Hazard");
		Transform* transform = new Transform(Vector2D(), Vector2D(100, 100));
		Sprite* sprite = new Sprite;

		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);

		hazard->AddComponent(transform);
		hazard->AddComponent(sprite);
		hazard->AddComponent(new ColliderRectangle(transform->GetScale() * 0.45f));

		Animation* animation = new Animation();
		hazard->AddComponent(animation);
		
		animation->Play(0, 4, 0.2f, true);

		return hazard;
	}

	GameObject* CreateEnemy(Mesh* mesh, SpriteSource* spriteSource)
	{
		GameObject* enemy = new GameObject("Enemy");
		Transform* transform = new Transform(Vector2D(), Vector2D(50, 50));
		Sprite* sprite = new Sprite;

		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);

		enemy->AddComponent(transform);
		enemy->AddComponent(sprite);
		enemy->AddComponent(new Physics);
		enemy->AddComponent(new ColliderRectangle);
		enemy->AddComponent(new Behaviors::Enemy);

		return enemy;
	}

	GameObject* CreateCheckpoint(Mesh* mesh, SpriteSource* spriteSource, Level* level) {

		GameObject* checkpoint = new GameObject("Checkpoint");
		checkpoint->AddComponent(new Transform(Vector2D(), Vector2D(100.0f, 100.0f)));

		Sprite* sprite = new Sprite;
		sprite->SetSpriteSource(spriteSource);
		sprite->SetMesh(mesh);
		checkpoint->AddComponent(sprite);

		checkpoint->AddComponent(new Animation());

		checkpoint->AddComponent(new ColliderRectangle(Vector2D(50.0f, 50.0f), Vector2D(0, 17.0f)));
		checkpoint->AddComponent(new LevelChanger(level));

		return checkpoint;
	}

	GameObject* CreateClickHelper()
	{
		GameObject* clickHelper = new GameObject("ClickHelper");
		Transform* transform = new Transform(Vector2D(), Vector2D(10, 10));
		
		clickHelper->AddComponent(transform);
		clickHelper->AddComponent(new ColliderCircle(10));
		clickHelper->AddComponent(new Behaviors::MouseClick);

		return clickHelper;
	}

	GameObject* CreateUIButton(Mesh* mesh, SpriteSource* spriteSource, Behaviors::UIButtonCallback callback)
	{
		GameObject* uiButton = new GameObject("UIButton");
		Sprite* sprite = new Sprite;
		Transform* transform = new Transform(Vector2D(), Vector2D(300, 75));
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);
		// Add components
		uiButton->AddComponent(transform);
		uiButton->AddComponent(sprite);
		uiButton->AddComponent(new ColliderRectangle(transform->GetScale()/2));
		uiButton->AddComponent(new Behaviors::UIButton(callback));

		return uiButton;
	}

	GameObject* CreateHelperCube(Mesh* mesh, SpriteSource* spriteSource)
	{
		GameObject* helperCube = new GameObject("HelperCube");
		Sprite* sprite = new Sprite;
		Transform* transform = new Transform(Vector2D(), Vector2D(50, 50));
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);

		// Add the components
		helperCube->AddComponent(transform);
		helperCube->AddComponent(sprite);
		helperCube->AddComponent(new ColliderRectangle(Vector2D(25,25)));
		Physics* rb = new Physics();

		rb->SetGravity(Vector2D(0, -100));
		helperCube->AddComponent(rb);

		return helperCube;
	}

	GameObject* CreateDebugLevelSwaper()
	{
		GameObject* DebugLevelSwaperGO = new GameObject("DebugLevelSwaper");
		
		DebugLevelSwaperGO->AddComponent(new DebugLevelSwaper());

		return DebugLevelSwaperGO;
	}

	GameObject* CreateExplosion(Mesh* mesh, SpriteSource* source)
	{
		GameObject* explosion = new GameObject("Explosion");
		Transform* transform = new Transform(Vector2D(), Vector2D(100, 100));
		explosion->AddComponent(transform);

		Sprite* sprite = new Sprite;
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(source);
		explosion->AddComponent(sprite);

		Animation* animation = new Animation;
		explosion->AddComponent(animation);

		explosion->AddComponent(new Behaviors::ExplosionTimer());

		return explosion;
	}
}
