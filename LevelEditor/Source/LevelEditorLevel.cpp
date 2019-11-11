//------------------------------------------------------------------------------
//
// File Name:	LevelEditorLevel.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <Space.h>
#include "LevelEditorLevel.h"
#include "LevelEditorUI.h"

//Components
#include <SpriteText.h>
#include <Transform.h>
#include <Physics.h>
#include <ColliderTilemap.h>
#include <SpriteTilemap.h>

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

Levels::LevelEditorLevel::LevelEditorLevel() : Level("LevelEditor")
{
}

void Levels::LevelEditorLevel::Load()
{
	std::cout << GetName() << "::Load" << std::endl;

	System::GetInstance().SetWindowTitle(WindowTitle);

	Graphics::GetInstance().GetCurrentCamera().Reset();

	////Register Custom Components

	SetFileLocation("Assets/Level2.lvl");
}

void Levels::LevelEditorLevel::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;

	LoadLevel(true);
}

void Levels::LevelEditorLevel::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void Levels::LevelEditorLevel::Shutdown()
{
	std::cout << GetName() << "::Shutdown" << std::endl;

	//Save();
}

void Levels::LevelEditorLevel::Unload()
{
	std::cout << GetName() << "::Unload" << std::endl;
}