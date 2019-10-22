/**
	* Author: David Wong
	* Project: CS230 Lab 7
	* Created: 27 Novemer 2018
**/

// Includes //
#include "stdafx.h"
#include "SpriteTilemap.h"

#include <Vector2D.h>			// Vector2D

#include "Tilemap.h"			// Tilemap
#include "Transform.h"			// Transform

// Public Member Functions //
SpriteTilemap::SpriteTilemap()
	: map(nullptr)
{

}

Component* SpriteTilemap::Clone() const
{
	return new SpriteTilemap(*this);
}

void SpriteTilemap::Draw()
{
	// Get the width and height of the map
	const int mapWidth = map->GetWidth();
	const int mapHeight = map->GetHeight();
	// Get the dimensions of every individual tile
	const Vector2D& spriteDimensions = transform->GetScale();
	// Use a double loop to draw every sprite
	for (unsigned i = 0; i < static_cast<unsigned>(mapWidth); ++i)
	{
		for (unsigned j = 0; j < static_cast<unsigned>(mapHeight); ++j)
		{
			// Get the cell's value
			int cellValue = map->GetCellValue(i, j);
			// If the cell value is empty, then skip because there is nothing to draw
			if (!cellValue)
				continue;

			// Set the frame equal to the value inside the map (this map is not the collidable one)
			SetFrame(cellValue-1);
			// Get the offset of the tile, where it is going to be drawn
			Vector2D offset = Vector2D(i * spriteDimensions.x, -1 * static_cast<int>(j) * spriteDimensions.y);
			// Finally, draw the sprite
			Sprite::Draw(offset);
		}
	}
}

// Mutators //
void SpriteTilemap::SetTilemap(const Tilemap* tilemap)
{
	map = tilemap;
}