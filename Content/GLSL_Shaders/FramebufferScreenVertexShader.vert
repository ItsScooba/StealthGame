//Vertex Shader for drawing a frame buffer to the screen, for now always used for drawing the frame buffer to the screen.

#version 330

layout( location = 0 ) in vec2 vertexPosition;				//Screen Coordinates of this vertex position.
layout( location = 1 ) in vec2 textureCoordinates;			//UV coordinate of the texture for this vertex.


//Output the texture coordinate to the fragment shader.
out vec2 texCoord;



void main()
{
	texCoord = textureCoordinates;
	gl_Position = vec4( vertexPosition.x, vertexPosition.y, 0.0f, 1.0f );
}