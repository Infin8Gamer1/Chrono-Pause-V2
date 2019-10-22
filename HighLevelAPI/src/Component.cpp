/**
* Author: David Wong
* Project: CS230 Project 2 (Game Object and Game Manager)
* File Name: Component.cpp
* Created: 8 Nov 2018
**/

// Include //
#include "stdafx.h"
#include "Component.h"

// Public Member Functions //

Component::Component(const std::string& name_)
	: BetaObject(name_)
{

}

GameObject* Component::GetOwner() const
{
	return reinterpret_cast<GameObject*>(GetParent());
}