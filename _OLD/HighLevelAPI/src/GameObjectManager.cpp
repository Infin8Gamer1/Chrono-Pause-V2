/**
* Author: David Wong
* Project: CS230 Project 2 (Game Object and Game Manager)
* File Name: GameObjectManager.cpp
* Created: 8 Nov 2018
**/
// Includes //
#include "stdafx.h"
#include "GameObjectManager.h"

#include "Space.h"			// Space
#include "GameObject.h"		// Game Object
#include "Collider.h"		// Collider

// Public Member Functions //
GameObjectManager::GameObjectManager(Space* space_)
	: BetaObject("ObjectManager"), fixedUpdateDt(1.0f/60.0f), timeAccumulator(0), numObjects(0), numArchetypes(0)
{
	SetParent(reinterpret_cast<BetaObject*>(space_));
	// Initialize all possible objects with nullptr
	for (unsigned i = 0; i < maxObjects; ++i)
	{
		gameObjectActiveList[i] = nullptr;
	}

	// Initialize all possible archetypes with nullptr
	for (unsigned i = 0; i < maxArchetypes; ++i)
	{
		gameObjectArchetypes[i] = nullptr;
	}
}

GameObjectManager::~GameObjectManager()
{
	Shutdown();
	Unload();
}

void GameObjectManager::Update(float dt)
{
	// Get the space
	Space* space = reinterpret_cast<Space*>(GetParent());
	// If we aren't paused, then update all the active objects
	if(!space->IsPaused())
	{
		VariableUpdate(dt);
		FixedUpdate(dt);
		CheckCollisions();
	}

	// Destroy any objects marked for destruction
	DestroyObjects();

	// Draw the remaining objects
	Draw();
}

void GameObjectManager::Shutdown()
{
	for (unsigned i = 0; i < numObjects; ++i)
	{
		delete gameObjectActiveList[i];
		gameObjectActiveList[i] = nullptr;
	}

	numObjects = 0;
}

void GameObjectManager::Unload()
{
	for (unsigned i = 0; i < numArchetypes; ++i)
	{
		delete gameObjectArchetypes[i];
		gameObjectArchetypes[i] = nullptr;
	}

	numArchetypes = 0;
}

void GameObjectManager::AddObject(GameObject& gameObject)
{
	// Don't add any more objects that we have space for
	if (numObjects >= maxObjects)
	{
		delete &gameObject;
		return;
	}

	// Set the parent to belong on the space
	gameObject.SetParent(GetParent());
	// Update the number of objects we have and keep track of the new object we have
	gameObject.Initialize();
	gameObjectActiveList[numObjects++] = &gameObject;
}

void GameObjectManager::AddArchetype(GameObject& archetype)
{
	// Don't add anymore archetypes that we have space for
	if (numArchetypes >= maxArchetypes)
	{
		delete &archetype;
		return;
	}

	// Update the number of archetypes we have and keep track of the new archetype
	gameObjectArchetypes[numArchetypes++] = &archetype;
}

GameObject* GameObjectManager::GetObjectByName(const std::string& name_) const
{
	// Find the first object with the same name
	for (unsigned i = 0; i < numObjects; ++i)
	{
		if (gameObjectActiveList[i]->GetName() == name_)
		{
			return gameObjectActiveList[i];
		}
	}
	return nullptr;
}

GameObject* GameObjectManager::GetArchetypeByName(const std::string& name_) const
{
	// Find the first object with the same name
	for (unsigned i = 0; i < numArchetypes; ++i)
	{
		if (gameObjectArchetypes[i]->GetName() == name_)
		{
			return gameObjectArchetypes[i];
		}
	}
	return nullptr;
}

unsigned GameObjectManager::GetObjectCount(const std::string& name_) const
{
	// The number of objects we find with the same name
	unsigned count = 0;
	// Count the number of objects we have
	for (unsigned i = 0; i < numObjects; ++i)
	{
		if (gameObjectActiveList[i]->GetName() == name_)
		{
			++count;
		}
	}
	return count;
}

// Private Member Functions
void GameObjectManager::VariableUpdate(float dt)
{
	// Update all of the objects
	for (unsigned i = 0; i < numObjects; ++i)
	{
		if(!gameObjectActiveList[i]->IsPaused())
			gameObjectActiveList[i]->Update(dt);
	}
}

void GameObjectManager::FixedUpdate(float dt)
{
	// Update all of the objects when fixedUpdateDt has passed
	timeAccumulator += dt;
	if (timeAccumulator < fixedUpdateDt)
		return;

	timeAccumulator -= fixedUpdateDt;
	for (unsigned i = 0; i < numObjects; ++i)
	{
		if(!gameObjectActiveList[i]->IsPaused())
		gameObjectActiveList[i]->FixedUpdate(fixedUpdateDt);
	}
}

void GameObjectManager::DestroyObjects()
{
	// Destroy any objects marked for destruction
	for (unsigned i = 0; i < numObjects; ++i)
	{
		GameObject* object = gameObjectActiveList[i];
		if (object->IsDestroyed())
		{
			delete object;
			// Update the number of objects
			--numObjects;

			// Ok, now fill in the empty void we just created by shifting any
			// remaining objects one to the left
			for (unsigned j = i; j < numObjects; ++j)
			{
				gameObjectActiveList[j] = gameObjectActiveList[j + 1];
			}
		}
	}
}

void GameObjectManager::Draw()
{
	for (unsigned i = 0; i < numObjects; ++i)
	{
		gameObjectActiveList[i]->Draw();
	}
}

void GameObjectManager::CheckCollisions()
{
	// Compare each object of the scene to every object in the scene for collisions
	// Start the O(n^2) process to do physics
	for (unsigned i = 0; i < numObjects; ++i)
	{
		// Save the first object to compare against everything else
		GameObject* firstObjectTested = gameObjectActiveList[i];
		if (firstObjectTested->IsDestroyed())
			continue;

		Collider* colliderA = reinterpret_cast<Collider*>(firstObjectTested->GetComponent("Collider"));
		// Only execute the collider code if the first object has a collider
		if (colliderA)
		{
			for (unsigned j = 0; j < numObjects; ++j)
			{
				// If we found the same object comparing to iself, then skip this check
				if (i == j)
					continue;

				GameObject* secondObjectTested = gameObjectActiveList[j];
				if (secondObjectTested->IsDestroyed())
					continue;

				const Collider* colliderB = reinterpret_cast<const Collider*>(secondObjectTested->GetComponent("Collider"));
				// Only execute the collider code if the second object has a collider
				if (colliderB)
				{
					// Check for the collision
					colliderA->CheckCollision(*colliderB);
				}
			}
		}
	}
}