#pragma once








#include <memory>

#include "Box2D\Box2D.h"
#include "Box2D\Common\b2Draw.h"

#include "GL\glew.h"

#include "Shader.h"
#include "Mesh.h"




//Class used to draw debug data to the screen related to physics.
class PhysicsDebugDraw : public b2Draw
{
public:


	PhysicsDebugDraw();
	~PhysicsDebugDraw();

	void DrawPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color );
	void DrawSolidPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color );
	void DrawCircle( const b2Vec2& center, float32 radius, const b2Color& color );
	void DrawSolidCircle( const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color );
	void DrawSegment( const b2Vec2& point1, const b2Vec2& point2, const b2Color& color );
	void DrawPoint( const b2Vec2& p, float32 size, const b2Color& color );
	void DrawTransform( const b2Transform& transform );
	

private:

	std::shared_ptr< Mesh > m_debugMesh;
};