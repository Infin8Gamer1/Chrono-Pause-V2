/**
	* Author: David Wong
	* Project: CS230 Project 3
	* Created: 30 Nov 2018
**/

// Includes //
#include "stdafx.h"
#include "Enemy.h"

#include <Random.h>				// Random
#include <Vector2D.h>			// Vector2D

#include "Component.h"			// Component
#include "Physics.h"			// Physics
#include "GameObject.h"			// Game Object
#include "Space.h"				// Space
#include "ColliderTilemap.h"	// Tilemap Collider

// Public Member Functions //
namespace Behaviors
{
	enum EnemyStates
	{
		IDLE, WANDER, CHASE
	};

	void EnemyMapCollisionHandler(GameObject& object, const MapCollision& collision);

	Enemy::Enemy()
		: Component("Enemy"), currentState(0), nextState(0), innerState(InnerStateEnter), timer(0.0f), stateChangeTime(5.0f),
		wanderDirection(0), wanderSpeed(200.f), gravity(0.0f, -1200.f)
	{
	}

	Component* Enemy::Clone() const
	{
		return new Enemy(*this);
	}

	void Enemy::Initialize()
	{
		physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
		player = GetOwner()->GetSpace()->GetObjectManager().GetObjectByName("Monkey");
#if _DEBUG
		if (!player)
		{
			std::cerr << "[ERROR]: Enemy could not find the player object" << std::endl;
		}
#endif
		Collider* collider = static_cast<Collider*>(GetOwner()->GetComponent("Collider"));
		collider->SetMapCollisionHandler(EnemyMapCollisionHandler);
	}

	void Enemy::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		// Apply the AI behavior
		switch (currentState)
		{
		case EnemyStates::IDLE:
			switch (innerState)
			{
			case InnerStates::InnerStateEnter:
				innerState = InnerStates::InnerStateUpdate;
				break;
			case InnerStates::InnerStateUpdate:
				break;
			case InnerStates::InnerStateExit:
				SetState(EnemyStates::WANDER);
				innerState = InnerStates::InnerStateEnter;
				break;
			}
			break;

		case EnemyStates::WANDER:
			// Apply the gravity
			physics->AddForce(gravity);
			switch (innerState)
			{
			case InnerStates::InnerStateEnter:
				// TO DO: Pick a direction to go to
				innerState = InnerStates::InnerStateUpdate;
				wanderDirection = RandomRange(0, 2) > 1 ? 1 : -1;
				break;
			case InnerStates::InnerStateUpdate:
				// TO DO: Wandering behavior
				physics->SetVelocity(Vector2D(wanderSpeed * wanderDirection, physics->GetVelocity().y));
				break;
			case InnerStates::InnerStateExit:
				physics->SetVelocity(Vector2D(0, physics->GetVelocity().y));
				SetState(EnemyStates::CHASE);
				innerState = InnerStates::InnerStateEnter;
				break;
			}
			break;

		case EnemyStates::CHASE:
			switch (innerState)
			{
			case InnerStates::InnerStateEnter:
				innerState = InnerStates::InnerStateUpdate;
				break;
			case InnerStates::InnerStateUpdate:
				// TO DO: Chasing behavior
				break;
			case InnerStates::InnerStateExit:
				SetState(EnemyStates::IDLE);
				innerState = InnerStates::InnerStateEnter;
				break;
			}
			break;
		}

		// Move on to the next state if necessary
		if (nextState != currentState)
		{
			currentState = nextState;
		}

		// Change the inner state
		timer += dt;
		if (timer >= stateChangeTime)
		{
			timer -= stateChangeTime;
			(++innerState) %= 3;
		}
	}

	void Enemy::SetState(unsigned nextState_)
	{
		nextState = nextState_;
	}

	void EnemyMapCollisionHandler(GameObject& object, const MapCollision& collision)
	{
		// If we collided with the map either to the right or left, then change the wander direction
		Enemy* enemy = static_cast<Enemy*>(object.GetComponent("Enemy"));
		if (collision.right || collision.left)
		{
			enemy->wanderDirection = collision.right ? -1 : 1;
		}
	}
}
