//Vertex Shader that handles transformations before drawing.

#version 330

//Transformation matrices.
uniform mat4 transformationMatrix;							//Model-View-Projection Transform Matrix.


layout( location = 0 ) in vec3 vertexPosition;				//X, Y, and Z position of the vertex.
layout( location = 1 ) in vec2 textureCoordinates;			//UV coordinate of the texture for this vertex.


//Output the texture coordinate to the fragment shader.
out vec2 texCoord;

void main()
{
	texCoord = textureCoordinates;
	gl_Position = transformationMatrix * vec4( vertexPosition, 1.0 );
}