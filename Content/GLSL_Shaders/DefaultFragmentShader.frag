#version 330


uniform vec4 materialColor = vec4( 0.5, 0.5, 0.5, 1.0 );				//Primitive Color Data for manually applying a provided color to this fragment.

out vec4 pixelColor;													//The final color to paint the pixel.


void main()
{
	vec4 texel = materialColor;

	if( texel.a < 0.4 )
		discard;

	pixelColor = texel;
}