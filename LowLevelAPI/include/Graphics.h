//------------------------------------------------------------------------------
//
// File Name:	Graphics.h
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

#include "Matrix2D.h"
#include "Color.h"
#include "Matrix3D.h"
#include "Camera.h"
#include "Texture.h"
#include "Shapes2D.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Matrix2D;
class Renderer;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

enum BlendMode
{
	BM_None = 0,
	BM_Blend,
	BM_Add,
	BM_Multiply,
	BM_Screen,

	// Keep this one last
	BM_Num
};

enum TextureFilterMode
{
	TM_NearestNeighbor = 0,
	TM_Bilinear,
	TM_Trilinear
};

enum RenderMode
{
	RM_None = -1,
	RM_Forward,

	// Keep this one last
	RM_Num,
};

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class Graphics
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	void Init(unsigned width, unsigned height);
	void FrameStart();
	void Draw(unsigned arrayObjectID, unsigned drawMode, unsigned numVertices);
	void FrameEnd();
	void Shutdown();

	void SetRenderMode(RenderMode mode);

	const Color& GetBackgroundColor() const;
	void SetBackgroundColor(const Color& color = Colors::Black);
	const Color& GetScreenTintColor() const;
	void SetScreenTintColor(const Color& color = Colors::White);
	void SetSpriteBlendColor(const Color& color = Colors::White);

	void SetBlendMode(BlendMode mode, bool forceSet = false);
	void SetTexture(Texture* texture, const Vector2D& uv = Vector2D());
	void SetTransform(const Matrix2D& matrix);
	void SetTransform(const Vector2D& translation, const Vector2D& scale = Vector2D(1.0f, 1.0f), float rotation = 0.0f);

	Camera& GetDefaultCamera();
	Camera& GetCurrentCamera();
	void SetCurrentCamera(Camera& camera); 

	const BoundingRectangle GetScreenWorldDimensions() const;

	Vector2D ScreenToWorldPosition(const Vector2D& screenPosition);

	// SETTINGS
	// Test whether vertical sync is currently on
	bool GetUseVsync() const;
	// Turn vertical sync on or off - will cause performance issues on some machines
	void SetUseVSync(bool useVsync);

	// Test whether the application is in fullscreen mode.
	bool IsFullScreen() const;
	// Set whether the window is fullscreen.
	void SetFullScreen(bool fullscreen);

	// Sets the resolution of the window.
	// Params:
	//   width = The new width of the window.
	//   height = The new height of the window.
	void SetResolution(unsigned width, unsigned height);

	// Gets the single instance of the Graphics class.
	static Graphics& GetInstance();

private:
	//------------------------------------------------------------------------------
	// Private Structures:
	//------------------------------------------------------------------------------

	enum OriginMode
	{
		OM_Normal = 0,
		OM_Top_Left,

		// Keep this one last
		OM_NUM,
	};

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Constructor and destructor are private to prevent accidental instantiation/deletion.
	Graphics();
	~Graphics();

	// Copy constructor and assignment are disabled.
	Graphics(const Graphics& other) = delete;
	Graphics& operator=(const Graphics& other) = delete;

	// Other private functions
	void SetViewport();
	void SetOriginMode(OriginMode mode, bool forceSet = false);
	void CreateContext();
	void InitRenderer();

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Colors and blending
	Color backgroundColor;
	Color tintColor;
	Color blendColor;
	BlendMode blendMode;

	// Textures
	Texture* defaultTexture;
	Texture* currentTexture;
	Vector2D textureCoords;
	float alpha;
	ULONG_PTR gdiplusToken; // GDI+ for loading textures

	// Viewport
	int viewportWidth;
	int viewportHeight;
	int windowPositionX;
	int windowPositionY;

	// Transformations
	OriginMode originMode;
	Matrix3D worldMatrix;
	Matrix3D viewMatrix;
	Matrix3D projectionMatrix;

	// Cameras
	Camera defaultCamera;
	Camera* currentCamera;

	// Renderer
	Renderer* renderers[RM_Num] = { nullptr };
	RenderMode renderModeCurrent;
	RenderMode renderModeNext;

	// Settings
	bool useVsync;
	bool fullscreen;
};

//------------------------------------------------------------------------------
