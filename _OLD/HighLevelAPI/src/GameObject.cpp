/**
* Author: David Wong
* Project: CS230 Project 2 (Game Object and Game Manager)
* File Name: GameObject.cpp
* Created: 8 Nov 2018
**/
// Includes //
#include "stdafx.h"
#include "GameObject.h"

#include "Component.h"			// Component

// Public Member Functions //
GameObject::GameObject(const std::string& name_)
	: BetaObject(name_), numComponents(0), isDestroyed(false), isPaused(false)
{
	// Set all the components to be a nullptr
	for (unsigned i = 0; i < 10; ++i)
	{
		components[i] = nullptr;
	}
}

GameObject::GameObject(const GameObject& gameObject)
	: BetaObject(gameObject.GetName()), isDestroyed(gameObject.isDestroyed), numComponents(gameObject.numComponents), isPaused(false)
{
	for (unsigned i = 0; i < 10; ++i)
	{
		if (i < numComponents)
		{
			components[i] = gameObject.components[i]->Clone();
			components[i]->SetParent(this);
		}
		else
			components[i] = nullptr;
	}
}

GameObject::~GameObject()
{
	// Clean up the components
	for (unsigned i = 0; i < numComponents; ++i)
	{
		delete components[i];
	}	
}

void GameObject::Initialize()
{
	for (unsigned i = 0; i < numComponents; ++i)
	{
		components[i]->Initialize();
	}
}

void GameObject::Update(float dt)
{
	for (unsigned i = 0; i < numComponents; ++i)
	{
		components[i]->Update(dt);
	}
}

void GameObject::FixedUpdate(float dt)
{
	for (unsigned i = 0; i < numComponents; ++i)
	{
		components[i]->FixedUpdate(dt);
	}
}

void GameObject::Draw()
{
	for (unsigned i = 0; i < numComponents; ++i)
	{
		components[i]->Draw();
	}
}

void GameObject::AddComponent(Component* component)
{
	component->SetParent(this);
	components[numComponents++] = component;
}

Component* GameObject::GetComponent(const std::string& name_)
{
	for (unsigned i = 0; i < numComponents; ++i)
	{
		if (name_ == components[i]->GetName())
			return components[i];
	}

	return nullptr;
}

void GameObject::Destroy()
{
	isDestroyed = true;
}

bool GameObject::IsDestroyed() const
{
	return isDestroyed;
}

void GameObject::SetPaused(bool paused)
{
	isPaused = paused;
}

bool GameObject::IsPaused() const
{
	return isPaused;
}

Space* GameObject::GetSpace() const
{
	return reinterpret_cast<Space*>(GetParent());
}