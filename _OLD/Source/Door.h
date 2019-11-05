//-----//------------------------------------------------------------------------------
//
// File Name:	Archetypes.h
// Author(s):	Sage Dupuy (sage.dupuy), David Wong (david.wongcascante)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once

#include "Component.h" // base class
#include <Color.h>	 // Color
#include <Vector2D.h>
#include <Collider.h>
#include <Physics.h>
#include <ColliderRectangle.h>

// Forward Declarations
class Animation;
class GameObject;
struct BoundingRectangle;
enum RectangleSide;

class Door : public Component
{
public:
	enum DoorType {
		Horizontal,
		Vertical
	};

    Door(DoorType type = DoorType::Horizontal);

    Component* Clone() const;

    void Initialize();

    void Update(float dt) override;

	// Handles the collisions between the door and other objects
	// Params:
	//   door: The door object we are testing the collision with
	//   other: The other object we are testing the collision with
	friend void DoorObjectCollisionHandler(GameObject& door, GameObject& other);

	//vars
    bool open;

	DoorType type;

	// Move an object and set its velocity based on where it collided with the tilemap.
	// Params:
	//   objectRectangle = A bounding rectangle that encompasses the object.
	//   objectTransform = Pointer to the object's transform component.
	//   objectPhysics = Pointer to the object's physics component.
	//   collisions = True/false values from map collision checks.
	void ResolveCollisions(const BoundingRectangle & objectRectangle, Transform * objectTransform, Physics * objectPhysics, const MapCollision & collisions);

private:
	// Find the center of the closest tile on the x-axis or y-axis.
	// Used for assisting in collision resolution on a particular side.
	// Params:
	//   side = Which side the collision is occurring on.
	//   sidePosition = The x or y value of that side.
	//   point = the objects position
	// Returns:
	//   The center of the closest tile to the given position on the given side.
	float GetNextTileCenter(RectangleSide side, float sidePosition);

	bool moving = false;
	bool openState = false;

    Collider* collider;
    Animation* animation;
};
