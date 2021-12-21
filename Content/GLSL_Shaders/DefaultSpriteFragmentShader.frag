#version 330



uniform vec4 materialColor = vec4( 0.0, 0.0, 0.0, 0.0 );					//Primitive Color Data for manually applying a provided color to this fragment.
uniform sampler2D activeTexture;										//The texture uniform variable that we are mapping.

in vec2 texCoord;														//The texture coordinate for mapping textures to vertices.

out vec4 pixelColor;													//The final color to paint the pixel.


void main()
{
	vec4 texel = texture( activeTexture, texCoord );
	texel.xyz = mix( texel.xyz, materialColor.xyz, materialColor.a );
	
	if( texel.a < 0.4 )
		discard;

	pixelColor = texel;
}