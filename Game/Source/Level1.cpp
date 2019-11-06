//------------------------------------------------------------------------------
//
// File Name:	Level1.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <Space.h>
#include "Level1.h"

//Components
#include <SpriteText.h>
#include <Transform.h>
#include <Physics.h>
#include <ColliderTilemap.h>
#include <SpriteTilemap.h>
#include "PlayerAnimController.h"
#include "PlayerMove.h"
#include "ExplosionTimer.h"
#include "Lava.h"
#include "MouseClick.h"
#include "UIButton.h"

//Resources
#include <Mesh.h>
#include <Color.h>
#include <Tilemap.h>
#include <SpriteSource.h>

//Systems
#include <GameObjectFactory.h>
#include <ResourceManager.h>
#include <System.h>
#include <Input.h>
#include <MeshHelper.h>
#include <Engine.h>
#include <SoundManager.h>
#include <Random.h>
#include <SpaceManager.h>
#include <Graphics.h>
#include <Parser.h>
#include <CameraController.h>


Levels::Level1::Level1() : Level("LevelEditor")
{
}

void Levels::Level1::Load()
{
	std::cout << GetName() << "::Load" << std::endl;

	System::GetInstance().SetWindowTitle(WindowTitle);

	Graphics::GetInstance().GetCurrentCamera().Reset();

	////Register Custom Components
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::PlayerAnimController>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::PlayerMove>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::ExplosionTimer>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::Lava>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::MouseClick>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::UIButton>();

	SetFileLocation("Assets/Level1.lvl");
}

void Levels::Level1::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;

	LoadLevel();

	cameraController = new CameraController(*GetSpace()->GetCamera());

	cameraController->Retarget(GetSpace()->GetObjectManager().GetObjectByName("Player"));
	cameraController->Reset();
	cameraController->SetSpeed(0.01f);
}

void Levels::Level1::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);


	// Update the camera controller
	cameraController->Follow();
}

void Levels::Level1::Shutdown()
{
	std::cout << GetName() << "::Shutdown" << std::endl;

	delete cameraController;
	cameraController = nullptr;
}

void Levels::Level1::Unload()
{
	std::cout << GetName() << "::Unload" << std::endl;
}