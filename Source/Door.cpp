
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
#include <stdafx.h>
#include "Door.h"					// Door

#include <GameObject.h>				// Game Object
#include <Space.h>					// Space
#include <Transform.h>				// Transform
#include <Animation.h>				// Animation
#include <ColliderTilemap.h>
#include <Shapes2D.h>

void DoorObjectCollisionHandler(GameObject& door, GameObject& other)
{
	if (other.GetName() == "Player" || other.GetName() == "HelperCube") {

		//get components
		Transform* otherTransform = static_cast<Transform*>(other.GetComponent("Transform"));
		Transform* doorTransform = static_cast<Transform*>(door.GetComponent("Transform"));
		Physics* otherPhysics = static_cast<Physics*>(other.GetComponent("Physics"));
		ColliderRectangle* otherCollider = static_cast<ColliderRectangle*>(other.GetComponent("Collider"));

		//create a bounding box for the other object
		BoundingRectangle otherRect = BoundingRectangle(otherTransform->GetTranslation(), otherCollider->GetExtents());

		//check collision sides and store it in a MapCollision var
		bool bottom = false, left = false, right = false, top = false;
		
		if (static_cast<Door*>(door.GetComponent("Door"))->type == Door::DoorType::Horizontal) {
			if (otherTransform->GetTranslation().x > doorTransform->GetTranslation().x) {
				left = true;
			}
			else {
				right = true;
			}
		} else if (static_cast<Door*>(door.GetComponent("Door"))->type == Door::DoorType::Vertical) {
			if (otherTransform->GetTranslation().y > doorTransform->GetTranslation().y) {
				bottom = true;
			}
			else {
				top = true;
			}
		}
		
		MapCollision mapCollision = MapCollision(bottom, top, left, right);
		

		static_cast<Door*>(door.GetComponent("Door"))->ResolveCollisions(otherRect, otherTransform, otherPhysics, mapCollision);

		/*Vector2D myGridPos = ColliderTilemap::ConvertWorldCordsToTileMapCords(static_cast<Transform*>(door.GetComponent("Transform"))->GetTranslation(), door.GetSpace());

		Transform* otherTransform = static_cast<Transform*>(other.GetComponent("Transform"));
		Physics* otherPhysics = static_cast<Physics*>(other.GetComponent("Physics"));
		Vector2D otherGridPos = ColliderTilemap::ConvertWorldCordsToTileMapCords(otherTransform->GetTranslation(), other.GetSpace());

		if (static_cast<Door*>(door.GetComponent("Door"))->type == Door::DoorType::Horizontal) {
			if (otherGridPos.x > myGridPos.x) {
				//get the new position
				Vector2D newPos = ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(floor(myGridPos.x) + 1, 0), door.GetSpace());
				newPos.y = otherTransform->GetTranslation().y;
				//Move that sucker
				otherTransform->SetTranslation(newPos);
				//set the x velocity to 0
				otherPhysics->SetVelocity(Vector2D(0, otherPhysics->GetVelocity().y));
			}
			else if (otherGridPos.x < myGridPos.x) {
				//get the new position
				Vector2D newPos = ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(floor(myGridPos.x) - 1, 0), door.GetSpace());
				newPos.y = otherTransform->GetTranslation().y;
				//Move that sucker
				otherTransform->SetTranslation(newPos);
				//set the x velocity to 0
				otherPhysics->SetVelocity(Vector2D(0, otherPhysics->GetVelocity().y));
			}
		}
		else if (static_cast<Door*>(door.GetComponent("Door"))->type == Door::DoorType::Vertical) {
			if (otherGridPos.y > myGridPos.y) {
				//get the new position
				Vector2D newPos = ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(0, floor(myGridPos.y) + 1), door.GetSpace());
				newPos.x = otherTransform->GetTranslation().x;
				//Move that sucker
				otherTransform->SetTranslation(newPos);
				//set the x velocity to 0
				otherPhysics->SetVelocity(Vector2D(otherPhysics->GetVelocity().x, 0));
			}
			else if (otherGridPos.y < myGridPos.y) {
				//get the new position
				Vector2D newPos = ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D(0, floor(myGridPos.y) - 1), door.GetSpace());
				newPos.x = otherTransform->GetTranslation().x;
				//Move that sucker
				otherTransform->SetTranslation(newPos);
				//set the x velocity to 0
				otherPhysics->SetVelocity(Vector2D(otherPhysics->GetVelocity().x, 0));
			}
		}*/
	}
}

void Door::ResolveCollisions(const BoundingRectangle & objectRectangle, Transform * objectTransform, Physics * objectPhysics, const MapCollision & collisions) {
	// Get the translation and velocity from the object and store them in variables
	Vector2D translation = objectTransform->GetTranslation();
	Vector2D velocity = objectPhysics->GetVelocity();

	// We need to determine how much to move the object
	float nudgeAmount;
	// We will do this by finding the center of the next tile, 
	// then finding the distance from the corresponding side to that position
	float nextTileCenter;

	//if the object is colliding on the bottom or top
	if (collisions.bottom || collisions.top)
	{
		//if the object is colliding on the bottom
		if (collisions.bottom)
		{
			// Find tile above the object's bottom side
			nextTileCenter = GetNextTileCenter(SideBottom, objectRectangle.bottom);
			// Find distance to next tile center
			nudgeAmount = nextTileCenter - objectRectangle.bottom;
		}
		else
		{
			// Find tile below object's top side
			nextTileCenter = GetNextTileCenter(SideTop, objectRectangle.top);
			// Find distance to next tile center
			nudgeAmount = nextTileCenter - objectRectangle.top;
		}

		// Nudge object up/down
		translation.y += nudgeAmount;
		// Stop velocity in y direction
		velocity.y = 0;
	}

	//if the object is colliding on the left or right
	if (collisions.left || collisions.right)
	{
		//if the object is colliding on the left
		if (collisions.left) {
			// Find tile to the right the object's left side
			nextTileCenter = GetNextTileCenter(SideLeft, objectRectangle.left);
			// Find distance to next tile center
			nudgeAmount = nextTileCenter - objectRectangle.left;
		}
		else {
			// Find tile to the left the object's right side
			nextTileCenter = GetNextTileCenter(SideRight, objectRectangle.right);
			// Find distance to next tile center
			nudgeAmount = nextTileCenter - objectRectangle.right;
		}

		// Nudge object left/right
		translation.x += nudgeAmount;
		// Stop velocity in x direction
		velocity.x = 0;
	}

	// Modify object's actual translation and velocity
	objectTransform->SetTranslation(translation);
	objectPhysics->SetVelocity(velocity);
}

float Door::GetNextTileCenter(RectangleSide side, float sidePosition)
{
	Vector2D point;

	// Create a pointer/reference variable to store the result
	float* result;

	//if the object is colliding on the bottom or top otherwise it is colliding on the left or right
	if (side == SideBottom || side == SideTop)
	{
		// Use the given position for the y-axis
		// Since we only care about one axis, the other will be 0
		point.y = sidePosition;
		// Remember which part we want to modify
		result = &point.y;
	} else {
		// Use the given position for the x-axis
		// Since we only care about one axis, the other will be 0
		point.x = sidePosition;
		// Remember which part we want to modify
		result = &point.x;
	}

	// Transform the world space point into tile space
	point = ColliderTilemap::ConvertWorldCordsToTileMapCords(point, GetOwner()->GetSpace());

	// Find the next tile index (higher or lower depending on the side)
	//if the object is colliding on the left or top
	if (side == SideLeft || side == SideTop) {
		*result = ceil(*result);
	}
	else {
		*result = floor(*result);
	}

	point -= Vector2D(0.5, 0.5);

	// Transform point back into world space
	point = ColliderTilemap::ConvertTileMapCordsToWorldCords(point, GetOwner()->GetSpace());

	return *result;
}

Door::Door(DoorType type) : Component("Door"), collider(nullptr), animation(nullptr), open(false), type(type)
{
}

Component * Door::Clone() const
{
    return new Door(*this);
}

void Door::Initialize()
{
    collider = static_cast<Collider*>(GetOwner()->GetComponent("Collider"));
    animation = static_cast<Animation*>(GetOwner()->GetComponent("Animation"));
    
	collider->SetCollisionHandler(DoorObjectCollisionHandler);
}

void Door::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	if (open) {
		collider->SetEnabled(false);
	}
	else {
		collider->SetEnabled(true);
	}

	if (!moving) {
		//if told to open door and door is closed
		if (open && !openState) {
			animation->Play(0, 4, 0.075f, false);
			moving = true;
		}
		//if told to close door and door is open
		if (!open && openState) {
			animation->Play(4, 4, 0.075f, false, true);
			moving = true;
		}
	} else if(!animation->IsRunning()){
		moving = false;
		openState = !openState;
	}
}
