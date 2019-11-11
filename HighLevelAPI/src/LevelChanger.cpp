//------------------------------------------------------------------------------
//
// File Name:	LevelChanger.cpp
// Author(s):	Jacob Holyfield (jacob.holyfield)
// Project:		Chrono-Pause-V2
//
//------------------------------------------------------------------------------

#include <stdafx.h>
#include "LevelChanger.h"

#include <Level.h>
#include <GameObject.h>
#include <Collider.h>
#include <Space.h>
#include <Animation.h>
#include <Engine.h>
#include <SoundManager.h>
#include <Parser.h>
#include <CameraController.h>

void LevelChangerObjectCollisionHandler(GameObject & current, GameObject & other)
{
	if (other.GetName() == "Player" && !current.GetSpace()->GetIsLevelEditor())
	{
		current.GetComponent<LevelChanger>()->LoadNextLevel = true;
	}
}

LevelChanger::LevelChanger() : Component("LevelChanger")
{
	LoadNextLevel = false;
	animationStarted = false;

	nextLevel = "";
	collider = nullptr;
	animation = nullptr;
	bar = nullptr;
}

LevelChanger::~LevelChanger()
{
	if (bar != nullptr)
	{
		TwRemoveVar(bar, "Next Level");
	}
}

void LevelChanger::Deserialize(Parser& parser)
{
	//get frame index
	parser.ReadVariable("nextLevel", nextLevel);
}

void LevelChanger::Serialize(Parser& parser) const
{
	//set frame index
	parser.WriteVariable("nextLevel", nextLevel);
}

void LevelChanger::AddVarsToTweakBar(TwBar* bar_)
{
	bar = bar_;

	Component::AddVarsToTweakBar(bar);
	std::string params = " group='" + GetName() + "' ";

	TwAddVarRW(bar, "Next Level", TW_TYPE_STDSTRING, &nextLevel, params.c_str());
}

Component * LevelChanger::Clone() const
{
    return new LevelChanger(*this);
}

void LevelChanger::Initialize()
{
    animation = GetOwner()->GetComponent<Animation>();
    collider = GetOwner()->GetComponent<Collider>();
    collider->SetCollisionHandler(LevelChangerObjectCollisionHandler);

	// Set the jump sound
	Engine::GetInstance().GetModule<SoundManager>()->AddEffect("teleport.wav");
}

void LevelChanger::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (LoadNextLevel){
		if (!animationStarted) {
			animation->Play(0.1f, false);
			animationStarted = true;
			Engine::GetInstance().GetModule<SoundManager>()->PlaySound("teleport.wav");
		}
		else if (!animation->IsRunning()) {
			GetOwner()->GetSpace()->GetLevel()->SetFileLocation(nextLevel);

			GetOwner()->GetSpace()->GetLevel()->cameraController->Retarget(static_cast<Transform*>(nullptr));
			GetOwner()->GetSpace()->RestartLevel();
		}
	}
}


