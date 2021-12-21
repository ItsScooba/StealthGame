//Vertex Shader that handles transformations before drawing.

#version 330

//Transformation matrices.
uniform mat4 transformationMatrix;							//Model-View-Projection Transform Matrix.


layout( location = 0 ) in vec3 vertexPosition;				//X, Y, and Z position of the vertex.



void main()
{
	gl_Position = transformationMatrix * vec4( vertexPosition, 1.0 );
}