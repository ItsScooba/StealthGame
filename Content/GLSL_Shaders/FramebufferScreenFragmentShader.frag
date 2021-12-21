#version 330


uniform sampler2D renderedSceneTexture;									//The texture uniform variable that we are mapping.

in vec2 texCoord;														//The texture coordinate for mapping textures to vertices.

out vec4 pixelColor;													//The final color to paint the pixel.


void main()
{
	vec4 texel = texture( renderedSceneTexture, texCoord );
	
	pixelColor = texel;
}