#version 330


uniform sampler2D activeTexture;										//The texture uniform variable that we are mapping.
uniform vec3 textColor;

in vec2 texCoord;														//The texture coordinate for mapping textures to vertices.

out vec4 pixelColor;													//The color to paint the pixel.


void main()
{
	vec4 texel = vec4( textColor, 1.0f ) * vec4( 1.0f, 1.0f, 1.0f,  texture( activeTexture, texCoord ).r );
	if( texel.a < 0.4 )
		discard;

	pixelColor = texel;
}