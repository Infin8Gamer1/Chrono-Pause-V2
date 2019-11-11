//------------------------------------------------------------------------------
//
// File Name:	LevelChanger.h
// Author(s):	Jacob Holyfield
// Project:		BetaFramework
//
//------------------------------------------------------------------------------
#pragma once

#include "Component.h" // base class

class Collider;
class Animation;

class LevelChanger : public Component
{
public:
    LevelChanger();

	~LevelChanger();

    Component* Clone() const;

	// Loads object data from a file.
	void Deserialize(Parser& parser) override;

	// Saves object data to a file.
	void Serialize(Parser& parser) const override;

	// Add Component Spific Vars to a Tweak Bar
	void AddVarsToTweakBar(TwBar* bar) override;

    void Initialize();

    void Update(float dt) override;

    friend void LevelChangerObjectCollisionHandler(GameObject& current, GameObject& other);

private:
    bool LoadNextLevel;
	bool animationStarted;

	std::string nextLevel;

	TwBar* bar;

    Collider* collider;
    Animation* animation;
    
};