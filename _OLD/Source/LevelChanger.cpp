//------------------------------------------------------------------------------
//
// File Name:	LevelChanger.cpp
// Author(s):	Jacob Holyfield (jacob.holyfield)
// Project:		Chrono-Pause
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include <stdafx.h>
#include "LevelChanger.h"
#include <GameObject.h>
#include <Collider.h>
#include "Door.h"
#include <Space.h>
#include <Animation.h>
#include <Engine.h>
#include <SoundManager.h>

void LevelChangerObjectCollisionHandler(GameObject & current, GameObject & other)
{
	if (other.GetName() == "Player")
	{
		static_cast<LevelChanger*>(current.GetComponent("LevelChanger"))->LoadNextLevel = true;
	}
}

LevelChanger::LevelChanger(Level * _level) : Component("LevelChanger")
{
	LoadNextLevel = false;
	animationStarted = false;

	nextLevel = _level;
	collider = nullptr;
	animation = nullptr;
}

LevelChanger::~LevelChanger()
{
	if(!LoadNextLevel)
		delete nextLevel;
}

Component * LevelChanger::Clone() const
{
    return new LevelChanger(*this);
}

void LevelChanger::Initialize()
{
    animation = static_cast<Animation*>(GetOwner()->GetComponent("Animation"));
    collider = static_cast<Collider*>(GetOwner()->GetComponent("Collider"));
    collider->SetCollisionHandler(LevelChangerObjectCollisionHandler);
}

void LevelChanger::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (LoadNextLevel){
		if (!animationStarted) {
			animation->Play(0, 14, 0.1f, false);
			animationStarted = true;
			Engine::GetInstance().GetModule<SoundManager>()->PlaySound("teleport.wav");
		}
		else if (!animation->IsRunning()) {
			GetOwner()->GetSpace()->SetLevel(nextLevel);
		}
		
	}
}


