//------------------------------------------------------------------------------
//
// File Name:	DebugLevelSwaper.h
// Author(s):	Jacob Holyfield
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once

#include "Component.h" // base class

class DebugLevelSwaper : public Component
{
public:
    DebugLevelSwaper();

    Component* Clone() const;

    void Initialize();

    void Update(float dt) override;
};