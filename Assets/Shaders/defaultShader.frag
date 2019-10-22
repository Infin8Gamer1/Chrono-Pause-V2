#version 330 core

uniform vec4 blendColor;
uniform vec4 tintColor;
uniform vec2 textureOffset;
uniform sampler2D diffuse;

in vec4 vertexColor;
in vec2 textureCoordinate;

out vec4 fragColor;

void main()
{
	vec2 offsetTexCoord = textureCoordinate + textureOffset;
	
	if(offsetTexCoord.x > 1.0)
		offsetTexCoord.x -= 1.0;
		
	if(offsetTexCoord.y > 1.0)
		offsetTexCoord.y -= 1.0;
		
	fragColor = texture2D(diffuse, offsetTexCoord) * vertexColor * blendColor * tintColor;
}
