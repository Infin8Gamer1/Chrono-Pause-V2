/**
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Project: CS230 Lab 4 -- Graphics
* File name: MeshHelper.cpp
**/

// Includes //
#include "stdafx.h"
#include "SpriteSource.h"

#include <Vector2D.h>

// Public Member Functions //

SpriteSource::SpriteSource(int numCols_, int numRows_, Texture* texture_)
	: numCols(numCols_), numRows(numRows_), texture(texture_)
{
}

// Accessors //

Texture* SpriteSource::GetTexture() const
{
	return texture;
}

unsigned SpriteSource::GetFrameCount() const
{
	return numCols * numRows;
}

void SpriteSource::GetUV(unsigned int frameIndex, Vector2D & textureCoords) const
{
	// The size that every frame takes up
	float deltaU = 1.0f / static_cast<float>(numCols);
	float deltaV = 1.0f / static_cast<float>(numRows);

	// Determine in which column and row we are in using a frame index
	unsigned U = frameIndex % numCols;
	unsigned V = frameIndex / numCols;
	// Return the top left corner of the texture coordinate
	textureCoords.x = U * deltaU;
	textureCoords.y = V * deltaV;
}