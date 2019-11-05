//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.h
// Author(s):	 Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Texture;
class Vector2D;
class Sprite;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------
// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
class SpriteSource
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Allocate a new sprite source object.
	// Params:
	//	 numCols = The number of columns in the sprite sheet.
	//	 numRows = The number of rows in the sprite sheet.
	//	 texture = A pointer to a texture that has been loaded by the Alpha Engine.
	SpriteSource(int numCols = 1, int numRows = 1, Texture* texture = nullptr);

	// Returns a pointer to the texture, for the purposes of rendering a sprite.
	// Returns:
	//	 A pointer to the sprite source texture.
	Texture* GetTexture() const;

	// Returns the maximum number of frames possible, given the dimensions of the sprite sheet.
	// Returns:
	//	 The calculated frame count.
	unsigned GetFrameCount() const;

	// Returns the UV coordinates of the specified frame in a sprite sheet.
	// Params:
	//	 frameIndex = A frame index within a sprite sheet.
	//   textureCoords = Reference to a Vector2D containing the UV/texture coordinates.
	void GetUV(unsigned int frameIndex, Vector2D& textureCoords) const;

	// Sprite is friend for deserialization only
	friend class Sprite;

private:
	// The dimensions of the sprite sheet.
	unsigned numRows;
	unsigned numCols;

	// Pointer to a texture created using the Alpha Engine.
	Texture* texture;

	// Texture name used for deserialization
	std::string tempTextureName;
};

//----------------------------------------------------------------------------
