/**
	* Author: David Wong
	* Email: david.wongcascante@digipen.edu
	* Project: CS230 Lab 4 -- Graphics
	* File name: MeshHelper.cpp
**/

// Includes //
#include "stdafx.h"
#include "MeshHelper.h"

#include <MeshFactory.h>	// Mesh Factory
#include <Vertex.h>			// Vertices
#include <Color.h>			// Color

// Global Helper Functions //

Mesh* CreateTriangleMesh(const Color& color1, const Color& color2, const Color& color3)
{
	// Prepare the mesh factory to create a triangle mesh
	MeshFactory::GetInstance().AddTriangle(Vertex(Vector2D(-0.5f, 0.5f), color1), Vertex(Vector2D(-0.5f, -0.5f), color2),
		Vertex(Vector2D(0.5f, 0.0f), color3));

	// Get the triangle mesh from the factory
	return MeshFactory::GetInstance().EndCreate();
}

Mesh* CreateQuadMesh(const Vector2D& textureSize, const Vector2D& extents)
{
	// Create the vertices for the quad based on the parameters
	Vertex quadVertices[] = 
	{
		Vertex(Vector2D(-extents.x,  extents.y), Vector2D(0, 0)),
		Vertex(Vector2D(-extents.x, -extents.y), Vector2D(0, textureSize.y)),
		Vertex(Vector2D( extents.x, -extents.y), Vector2D(textureSize.x, textureSize.y)),
		Vertex(Vector2D( extents.x,  extents.y), Vector2D(textureSize.x, 0)),
	};

	// Prepare the mesh factory to create a quad
	MeshFactory::GetInstance().AddTriangle(quadVertices[3], quadVertices[0], quadVertices[1]);
	MeshFactory::GetInstance().AddTriangle(quadVertices[1], quadVertices[2], quadVertices[3]);
	
	// Finally create the mesh
	return MeshFactory::GetInstance().EndCreate();
}