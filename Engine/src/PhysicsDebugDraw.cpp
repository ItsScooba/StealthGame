#include "PhysicsDebugDraw.h"



#include "Engine.h"
#include "ResourceManager.h"
#include "Renderer.h"



#include "PhysicsComponent.h"








PhysicsDebugDraw::PhysicsDebugDraw() : m_debugMesh( new Mesh() )
{

}




PhysicsDebugDraw::~PhysicsDebugDraw()
{

}




void PhysicsDebugDraw::DrawPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color ) 
{

}




void PhysicsDebugDraw::DrawSolidPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color )
{
	std::vector< float > vertexData = {
		vertices[0].x, 512.0f, vertices[0].y,
		vertices[1].x, 512.0f, vertices[1].y,
		vertices[2].x, 512.0f, vertices[2].y,
		vertices[3].x, 512.0f, vertices[3].y,

	};

	std::vector< int > indexData = {
		0, 1, 2, 2, 3, 0
	};

	m_debugMesh->SetVertexData( vertexData );
	m_debugMesh->SetIndexData( indexData );

	glm::mat4 transform = Engine::GetInstance().GetGameScene()->GetPlayerController()->GetCamera().GetViewMatrix();
	

	m_debugMesh->SetTransform( transform );
	m_debugMesh->GetMaterial()->AddMaterialParameter( "materialColor", std::shared_ptr< VectorParameter >( new VectorParameter( "materialColor", color.r, color.g, color.b, 1.0f ) ) );

	Engine::GetInstance().GetRenderer().DrawMesh( m_debugMesh );
}





void PhysicsDebugDraw::DrawCircle( const b2Vec2& center, float32 radius, const b2Color& color )
{

}





void PhysicsDebugDraw::DrawSolidCircle( const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color )
{
	const int numPoints = 30;
	int theta = 0;
	std::vector< float > vertexPositions;
	while( theta < 360 ) {

		vertexPositions.push_back( center.x + ( radius * glm::cos( theta * DEGREES_TO_RADIANS ) ) );
		vertexPositions.push_back( 512.0f );
		vertexPositions.push_back( center.y + ( radius * glm::sin( theta * DEGREES_TO_RADIANS ) ) );

		theta = theta + ( 360 / numPoints );
	}

	

	m_debugMesh->SetVertexData( vertexPositions );

	glm::mat4 transform = Engine::GetInstance().GetGameScene()->GetPlayerController()->GetCamera().GetViewMatrix();


	m_debugMesh->SetTransform( transform );
	m_debugMesh->GetMaterial()->AddMaterialParameter( "materialColor", std::shared_ptr< VectorParameter >( new VectorParameter( "materialColor", color.r, color.g, color.b, 1.0f ) ) );

	glm::mat4 modelTransform = Engine::GetInstance().GetGameScene()->GetPlayerController()->GetCamera().GetProjectionMatrix() * m_debugMesh->GetModelTransform();
	m_debugMesh->GetMaterial()->BindInstanceParameters();
	m_debugMesh->GetMaterial()->SetUniform( "transformationMatrix", modelTransform );
	glDrawArrays( GL_TRIANGLE_FAN, 0, m_debugMesh->GetNumVertices() );
}





void PhysicsDebugDraw::DrawSegment( const b2Vec2& point1, const b2Vec2& point2, const b2Color& color )
{

}




void PhysicsDebugDraw::DrawPoint( const b2Vec2& p, float32 size, const b2Color& color )
{

}





void PhysicsDebugDraw::DrawTransform( const b2Transform& transform )
{

}