#version 330 core

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 worldMatrix;

in vec4 positionAttribute;
in vec4 vertexColorAttribute;
in vec2 textureCoordinateAttribute;

out vec4 vertexColor;
out vec2 textureCoordinate;

void main()										
{						
	vertexColor = vertexColorAttribute;
	textureCoordinate = textureCoordinateAttribute;
	gl_Position = projectionMatrix * viewMatrix * worldMatrix * positionAttribute;
}
