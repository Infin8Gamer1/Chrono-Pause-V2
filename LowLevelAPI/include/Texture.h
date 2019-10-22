//------------------------------------------------------------------------------
//
// File Name:	Texture.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		Beta Engine
// Course:		WANIC VGP2
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Color.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Texture
{
public:
	//------------------------------------------------------------------------------
	// Public Functions
	//------------------------------------------------------------------------------

	// Creates a 1x1 white texture
	Texture();
	// Loads a texture from an array
	Texture(const std::vector<Color>& colors, unsigned width, unsigned height);
	// Destroys texture data via OpenGL
	~Texture();

	// Returns the filename of the texture.
	const std::string& GetName() const;
	// Returns the ID of the texture buffer in OpenGL.
	unsigned GetBufferID() const;

	// Loads a texture from a file
	static Texture* CreateTextureFromFile(const std::string& filename);

	// Gets the current relative path for textures
	static const std::string& GetFilePath();

private:
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Helper constructor for TextureFromFile
	Texture(const std::string& filename, Gdiplus::Bitmap& bitmap, Gdiplus::Rect& rect);

	// Loads a texture from an array
	void CreateTextureFromArray(const std::vector<Color>& colors, unsigned width, unsigned height);

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	unsigned bufferID;
	std::string filename;

	static std::string texturePath;
};

//------------------------------------------------------------------------------
