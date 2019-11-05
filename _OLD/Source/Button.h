//------------------------------------------------------------------------------
//
// File Name:	Archetypes.h
// Author(s):	Sage Dupuy (sage.dupuy)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once

#include "Component.h" // base class

class Collider;
class Sprite;

class Button : public Component
{
public:
	Button(GameObject* door);

    Button(std::vector<GameObject*> doors);

    Component* Clone() const;

    void Initialize();

    void Update(float dt) override;

    friend void ButtonObjectCollisionHandler(GameObject& current, GameObject& other);

private:
    bool Pressed;
    std::vector<GameObject*> doors;
    Collider* collider;
    Sprite* sprite;
    
};