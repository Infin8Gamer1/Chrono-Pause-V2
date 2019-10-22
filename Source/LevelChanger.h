//------------------------------------------------------------------------------
//
// File Name:	LevelChanger.h
// Author(s):	Jacob Holyfield
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once

#include "Component.h" // base class
#include <Level.h>

class Collider;
class Animation;

class LevelChanger : public Component
{
public:
    LevelChanger(Level* level);

	~LevelChanger();

    Component* Clone() const;

    void Initialize();

    void Update(float dt) override;

    friend void LevelChangerObjectCollisionHandler(GameObject& current, GameObject& other);

private:
    bool LoadNextLevel;
	bool animationStarted;

	Level* nextLevel;
    Collider* collider;
    Animation* animation;
    
};