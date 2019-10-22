/**
	* Author: David Wong
	* Project: CS230 Lab 7
	* Created: 27 November 2018
**/

// Includes //
#include "stdafx.h"
#include "ColliderTilemap.h"

#include <DebugDraw.h>				// Debug Draw
#include <Graphics.h>				// Graphics

#include "GameObject.h"				// Game Object
#include "Tilemap.h"				// Tilemap
#include "ColliderRectangle.h"		// Collider Rectangle
#include "Transform.h"				// Transform
#include "Physics.h"				// Physics
#include <Space.h>

// Public Member Functions //
ColliderTilemap::ColliderTilemap()
	: Collider(ColliderType::ColliderTypeTilemap), map(nullptr)
{

}

Component* ColliderTilemap::Clone() const
{
	return new ColliderTilemap(*this);
}

void ColliderTilemap::Draw()
{
	// Ignore this debug draw stage if the map doesn't exist
	if (!map)
		return;
	// Do a debug draw of every tile map collider we have
	DebugDraw& debugDraw = DebugDraw::GetInstance();
	Graphics& graphics = Graphics::GetInstance();
	// Map width and height
	int mapWidth = map->GetWidth();
	int mapHeight = map->GetHeight();
	// Tile map dimensions
	const Vector2D& tileDimensions = transform->GetScale();
	// Draw a rectangle for every tile we have on collision
	for (unsigned i = 0; i < static_cast<unsigned>(mapWidth); ++i)
	{
		for (int j = 0; j < mapHeight; ++j)
		{
			Vector2D center = Vector2D(i * tileDimensions.x + tileDimensions.x/2.0f, -j * tileDimensions.y + tileDimensions.y/2.0f);
			center += transform->GetTranslation();
			debugDraw.AddRectangle(center, tileDimensions, graphics.GetCurrentCamera(), Colors::Green);
		}
	}
}

bool ColliderTilemap::IsCollidingWith(const Collider& collider) const
{
	Transform* otherTransform = static_cast<Transform*>(collider.GetOwner()->GetComponent("Transform"));
	switch (collider.GetType())
	{
	case ColliderType::ColliderTypeRectangle:
		{
			const ColliderRectangle& otherColider = reinterpret_cast<const ColliderRectangle&>(collider);
			BoundingRectangle otherRectangle = BoundingRectangle(otherTransform->GetTranslation() + otherColider.GetOffset(), otherColider.GetExtents());
			// Get the rigid body of the other collider
			Physics* rigidBody = reinterpret_cast<Physics*>(collider.GetOwner()->GetComponent("Physics"));
			MapCollision collisions(false, false, false, false);
			// Whether the other object is colliding with the object
			bool colliding = false;
			for (unsigned i = 0; i < RectangleSide::SideCount; ++i)
			{
				// Check every side of the rectangle to see if it is colliding
				RectangleSide currentSide = static_cast<RectangleSide>(i);
				bool result = IsSideColliding(otherRectangle, currentSide);
				if (result)
				{
					colliding = true;
				}
				// Inform the map collisions whichs side did collide
				*(reinterpret_cast<bool*>(&collisions) + i) = result;
			}
			if (colliding)
			{
				MapCollisionEventHandler colliderHandler = collider.GetMapCollisionHandler();
				if (colliderHandler)
				{
					colliderHandler(*collider.GetOwner(), collisions);
				}
				if (rigidBody)
				{
					ResolveCollisions(otherRectangle, otherTransform, rigidBody, collisions);
				}
			}
			return colliding;
		}
	default:
		break;
	}

	return false;
}

bool ColliderTilemap::IsSideColliding(const BoundingRectangle& rectangle, RectangleSide side) const
{
	// Define the max amount of hotspots we got
#define MAX_HOTSPOTS 3
	// Create the hotspots
	Vector2D hotspotStep;
	Vector2D corner;
	// Visualize the collision points
	static DebugDraw& debugDraw(DebugDraw::GetInstance());
	static Graphics& graphics(Graphics::GetInstance());
	// See how many hotspots we are going to create
	Vector2D direction;
	switch (side)
	{
	case RectangleSide::SideBottom:
		direction = Vector2D(0, -1);
		break;
	case RectangleSide::SideTop:
		direction = Vector2D(0, 1);
		break;
	case RectangleSide::SideRight:
		direction = Vector2D(1, 0);
		break;
	case RectangleSide::SideLeft:
		direction = Vector2D(-1, 0);
		break;
	}
	int numHotspots = static_cast<int>(MAX_HOTSPOTS);
	// If there are no hotspots, then return early from the function
	if (numHotspots <= 0)
		numHotspots = 1;

	// Create a hotspot step that goes in a direction parallel to the side we are checking for
	switch (side)
	{
	case RectangleSide::SideBottom:
		hotspotStep = Vector2D(2.0f * rectangle.extents.x, 0);
		corner = Vector2D(-1.0f * rectangle.extents.x, -1.0f * rectangle.extents.y) + rectangle.center;
		break;
	case RectangleSide::SideTop:
		hotspotStep = Vector2D(2.0f * rectangle.extents.x, 0);
		corner = Vector2D(-1.0f * rectangle.extents.x, rectangle.extents.y) + rectangle.center;
		break;

	case RectangleSide::SideRight:
		hotspotStep = Vector2D(0, 2.0f * rectangle.extents.y);
		corner = Vector2D(rectangle.extents.x, -1.0f * rectangle.extents.y) + rectangle.center;
		break;
	case RectangleSide::SideLeft:
		hotspotStep = Vector2D(0, 2.0f * rectangle.extents.y);
		corner = Vector2D(-1.0f * rectangle.extents.x, -1.0f * rectangle.extents.y) + rectangle.center;
		break;
	}

	// After defining all of that set up, create the hotspots and testing for each one
	for (unsigned i = 0; i < static_cast<unsigned>(numHotspots); ++i)
	{
		corner += (hotspotStep / static_cast<float>(numHotspots+1));
		bool result = IsCollidingAtPosition(corner.x, corner.y);
		// Return whether the collision happened if did happen,
		// if not, then wait until another one does happen
		debugDraw.AddCircle(corner, 5.f, graphics.GetCurrentCamera(), result ? Colors::Red : Colors::Green);
		if (result)
			return true;
	}
	// If no collisions happened, then return false
	return false;
}

bool ColliderTilemap::IsCollidingAtPosition(float x, float y) const
{
	// Create the normalized tile coordinate
	Vector2D normalizedTileCoord = transform->GetInverseMatrix() * (Vector2D(x, y));
	// Find the index of the tile we are in
	int xIndex = static_cast<int>(normalizedTileCoord.x + 0.5f);
	int yIndex = static_cast<int>(-normalizedTileCoord.y + 0.5f);
	//std::cout << "Current Index: (" << xIndex << ", " << yIndex << ")" << std::endl;
	// If the indices are outside the boundaries of our tilemap, then ignore the rest of the collision code
	if (xIndex >= 0 && xIndex < static_cast<int>(map->GetWidth()) && yIndex >= 0 && yIndex < static_cast<int>(map->GetHeight()))
	{
		int cellValue = map->GetCellValue(xIndex, yIndex);
		return cellValue;
	}

	return false;
}

void ColliderTilemap::ResolveCollisions(const BoundingRectangle& objectRectangle, Transform* objectTransform,
	Physics* objectPhysics, const MapCollision& collisions) const
{
	// Calculate collision resolution adjustment on tilemap location and tile size
	Vector2D mapTranslation = transform->GetTranslation();
	Vector2D tileScale = transform->GetScale();
	float nextTileCenter = 0.0f;
	// How far we need to move the object out of the tilemap
	float nudgeAmount = 0.0f;
	// Velocity and Translation
	Vector2D objectTranslation = objectTransform->GetTranslation();
	Vector2D objectVelocity = objectPhysics->GetVelocity();

	if (collisions.bottom || collisions.top)
	{
		if (collisions.bottom)
		{
			// Find the tile on the bottom of where we are right now
			nextTileCenter = GetNextTileCenter(RectangleSide::SideBottom, objectRectangle.bottom);
			// Describe the nudge amount
			nudgeAmount = nextTileCenter - objectRectangle.bottom;
		}
		else
		{
			// Do the same for the top
			nextTileCenter = GetNextTileCenter(RectangleSide::SideTop, objectRectangle.top);
			nudgeAmount = nextTileCenter - objectRectangle.top;
		}
		// If it is the bottom or the top of the collider, snap the rectangle collider and change the y velocity
		objectTranslation.y += nudgeAmount;
		objectVelocity.y = 0;
	}
	
	if (collisions.right || collisions.left)
	{
		if (collisions.right)
		{
			nextTileCenter = GetNextTileCenter(RectangleSide::SideRight, objectRectangle.right);
			nudgeAmount = nextTileCenter - objectRectangle.right;
		}
		else
		{
			nextTileCenter = GetNextTileCenter(RectangleSide::SideLeft, objectRectangle.left);
			nudgeAmount = nextTileCenter - objectRectangle.left;
		}

		// If it is the right or left of the collider, snap the rectangle collider and change the x velocity
		objectTranslation.x += nudgeAmount;
		objectVelocity.x = 0;
	}

	objectTransform->SetTranslation(objectTranslation);
	objectPhysics->SetVelocity(objectVelocity);
}

float ColliderTilemap::GetNextTileCenter(RectangleSide side, float sidePosition) const
{
	// The point in space that is colliding
	Vector2D position;
	// The specific part of the center of the tile we care about
	float* center = &position.x;

	// If we are dealing with the top or bottom
	if (side == RectangleSide::SideTop || side == RectangleSide::SideBottom)
	{
		position = Vector2D(0, sidePosition);
		center = &position.y;
	}
	else
	{
		position = Vector2D(sidePosition, 0);
		//center = &position.x;
	}

	// Transform the point into tilemap space
	position = transform->GetInverseMatrix() * position;
	// Flip the Y-Axis
	position.y *= -1;
	// Move into the middle of the cell
	position += Vector2D(0.5f, 0.5f);
	// Find the tile next ot this one
	if (side == RectangleSide::SideLeft || side == RectangleSide::SideTop)
	{
		*center = ceilf(*center);
	}
	else
	{
		*center = floorf(*center);
	}

	// Re-adjust the position to be in world space
	position -= Vector2D(0.5f, 0.5f);
	position.y *= -1;
	position = transform->GetMatrix() * position;
	// Return how far away we are from the next tile
	return *center;
}

// Mutators //
void ColliderTilemap::SetTilemap(const Tilemap* tileMap)
{
	map = tileMap;
}

Vector2D ColliderTilemap::ConvertWorldCordsToTileMapCords(Vector2D inputCords, Space* space)
{
	ColliderTilemap* me = static_cast<ColliderTilemap*>(space->GetObjectManager().GetObjectByName("Tilemap")->GetComponent("Collider"));

	// Transform the world space point into tile space
	Vector2D point = me->transform->GetInverseMatrix() * inputCords;
	// Flip the y-axis
	point.y = -point.y;
	// Move completely into cell
	point += Vector2D(0.5, 0.5);

	return point;
}

Vector2D ColliderTilemap::ConvertTileMapCordsToWorldCords(Vector2D inputCords, Space* space) {
	ColliderTilemap* me = static_cast<ColliderTilemap*>(space->GetObjectManager().GetObjectByName("Tilemap")->GetComponent("Collider"));

	Vector2D Output = Vector2D(inputCords.x, inputCords.y * -1);
	Output = me->transform->GetMatrix() * Output;

	return Vector2D(Output.x, Output.y);
}