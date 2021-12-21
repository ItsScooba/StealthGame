#include "CubeMesh.h"













CubeMesh::CubeMesh( float width, float height, float depth ) : Mesh()
{
	std::vector< float > vertexData;
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;
	float halfDepth = depth / 2.0f;

	//BACK.
	vertexData.push_back( -halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( halfDepth );
	vertexData.push_back( -halfWidth );	vertexData.push_back( height );	vertexData.push_back( halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( height );	vertexData.push_back( halfDepth );
	vertexData.push_back( -halfWidth );	vertexData.push_back( height );	vertexData.push_back( halfDepth );

	//TOP.
	vertexData.push_back( -halfWidth );	vertexData.push_back( height );	vertexData.push_back( -halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( height );	vertexData.push_back( -halfDepth );
	vertexData.push_back( -halfWidth );	vertexData.push_back( height );	vertexData.push_back( halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( height );	vertexData.push_back( -halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( height );	vertexData.push_back( halfDepth );
	vertexData.push_back( -halfWidth );	vertexData.push_back( height );	vertexData.push_back( halfDepth );

	//FRONT.
	vertexData.push_back( -halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( -halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( -halfDepth );
	vertexData.push_back( -halfWidth );	vertexData.push_back( height );	vertexData.push_back( -halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( -halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( height );	vertexData.push_back( -halfDepth );
	vertexData.push_back( -halfWidth );	vertexData.push_back( height );	vertexData.push_back( -halfDepth );

	//BOTTOM
	vertexData.push_back( -halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( -halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( -halfDepth );
	vertexData.push_back( -halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( -halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( halfDepth );
	vertexData.push_back( -halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( halfDepth );

	//LEFT.
	vertexData.push_back( -halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( -halfDepth );
	vertexData.push_back( -halfWidth );	vertexData.push_back( height );	vertexData.push_back( -halfDepth );
	vertexData.push_back( -halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( halfDepth );
	vertexData.push_back( -halfWidth );	vertexData.push_back( height );	vertexData.push_back( -halfDepth );
	vertexData.push_back( -halfWidth );	vertexData.push_back( height );	vertexData.push_back( halfDepth );
	vertexData.push_back( -halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( halfDepth );

	//RIGHT.
	vertexData.push_back( halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( -halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( height );	vertexData.push_back( -halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( height );	vertexData.push_back( -halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( height );	vertexData.push_back( halfDepth );
	vertexData.push_back( halfWidth );	vertexData.push_back( 0.0f );	vertexData.push_back( halfDepth );

	SetVertexData( vertexData );
}




CubeMesh::~CubeMesh()
{

}