/**
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Project: CS230 Lab 4 -- Graphics
* File name: MeshHelper.cpp
**/

// Includes //
#include "stdafx.h"
#include "Sprite.h"

#include <Graphics.h>			// Graphics
#include <Mesh.h>				// Mesh

#include "GameObject.h"			// Game Object
#include "Transform.h"			// Transform
#include "Matrix2DStudent.h"	// CS230::Matrix2D
#include "SpriteSource.h"		// Sprite Source

// Public Member Functions
Sprite::Sprite()
: Component("Sprite"), frameIndex(0), spriteSource(nullptr), mesh(nullptr), transform(nullptr)
{

}

void Sprite::Initialize()
{
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
}

Component* Sprite::Clone() const
{
	return new Sprite(*this);
}

void Sprite::Draw(const Vector2D& offset)
{
	UNREFERENCED_PARAMETER(offset);
	// Only Draw the sprite if the mesh exists
	if (!mesh)
		return;

	// Check if we have a valid sprite source
	if (spriteSource)
	{
		Vector2D spriteSourceTexCoords;
		// Get the source's texture coordinates
		spriteSource->GetUV(frameIndex, spriteSourceTexCoords);
		// Set this sprite's texture into graphics
		Graphics::GetInstance().SetTexture(spriteSource->GetTexture(), spriteSourceTexCoords);
	}
	else
	{
		Graphics::GetInstance().SetTexture(nullptr);
	}

	Graphics::GetInstance().SetSpriteBlendColor(color);
	// Set the scale so that we can see it
	CS230::Matrix2D offsetMatrix = CS230::Matrix2D::TranslationMatrix(offset.x, offset.y);
	offsetMatrix *= transform->GetMatrix();

	Graphics::GetInstance().SetTransform(reinterpret_cast<const Matrix2D&>(offsetMatrix));

	// Finally, draw the mesh
	mesh->Draw();
}

void Sprite::Draw()
{
	Sprite::Draw(Vector2D());
}

// Simple Accessors //

float Sprite::GetAlpha() const
{
	return color.a;
}

unsigned Sprite::GetFrame() const
{
	return frameIndex;
}

const Color& Sprite::GetColor() const
{
	return color;
}

// Simple Mutators //

void Sprite::SetFrame(unsigned int frameIndex_)
{
	// Don't set the frame if the sprite source doesn't exist
	if (!spriteSource)
		return;

	// Check that the index fits inside the amount of frames we've got
	if (frameIndex_ < spriteSource->GetFrameCount())
	{
		// Set the animation to start on a new frame
		frameIndex = frameIndex_;
	}
}

void Sprite::SetAlpha(float alpha)
{
	// Change the color's alpha
	color.a = alpha;
}

void Sprite::SetMesh(Mesh* mesh_)
{
	mesh = mesh_;
}

void Sprite::SetColor(Color color_)
{
	color = color_;
}

void Sprite::SetSpriteSource(SpriteSource* spriteSource_)
{
	spriteSource = spriteSource_;
}