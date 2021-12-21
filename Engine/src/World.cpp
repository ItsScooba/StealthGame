#include "World.h"

#include "Engine.h"
#include "ResourceManager.h"

#include "PhysicsContactListener.h"

#include "Mesh.h"
#include "DefaultSpriteMaterial.h"

#include "EventEntitySpawned.h"
#include "EventEntityDestroyed.h"
#include "PostRenderEvent.h"

#include "RenderComponent.h"
#include "PhysicsComponent.h"

#include "../../src/CubeMesh.h"

#include "PhysicsDebugDraw.h"









World::World() : TILES_WIDE( 48 ), TILES_HIGH( 32 ), TILE_SIZE( 64 ), physics_simulation( new b2World( b2Vec2( 0.0f, 0.0f ) ) )
{
}




World::~World()
{
	delete physics_simulation;
}




bool World::Initialize()
{
	if ( !ResourceManager::GetInstance().LoadTextureAtlas( "Tiles" ) ) return false;

	m_worldGameObject.reset( new GameObject() );
	
	GenerateTerrain();
	GenerateMesh();

	PhysicsContactListener* physicsContactListener = new PhysicsContactListener();
	physics_simulation->SetContactListener( physicsContactListener );
	
	PhysicsDebugDraw* physicsDebugDraw = new PhysicsDebugDraw();
	physicsDebugDraw->AppendFlags( physicsDebugDraw->e_shapeBit );
	physics_simulation->SetDebugDraw( physicsDebugDraw );


	EventListener postRenderListener = fastdelegate::MakeDelegate( this, &World::OnPostRenderEvent );
	Engine::GetInstance().GetEventDispatcher().RegisterEventListener( EventType::POST_RENDER, postRenderListener );

	Engine::GetInstance().GetEventDispatcher().FireEvent( new EventEntitySpawned( m_worldGameObject ) );

	return true;
}




void World::Shutdown()
{
	EventListener postRenderListener = fastdelegate::MakeDelegate( this, &World::OnPostRenderEvent );
	Engine::GetInstance().GetEventDispatcher().UnregisterEventListener( EventType::POST_RENDER, postRenderListener );

	while ( !m_gameObjects.empty() ) {
		DestroyEntity( m_gameObjects.front() );
	}

	Engine::GetInstance().GetEventDispatcher().FireEvent( new EventEntityDestroyed( m_worldGameObject ) );
}




//Update the state of the game world.
void World::Tick()
{
	static const int velocityIterations = 5, static const positionIterations = 5;
	static const float timeStep = 1.0f / 60.0f;
	physics_simulation->Step( timeStep, velocityIterations, positionIterations );
}




//Spawn an entity game object into the world, and start updating it as an active object.
void World::SpawnEntity( std::shared_ptr< GameObject > gameObject )
{	
	m_gameObjects.push_back( gameObject );
	Engine::GetInstance().GetEventDispatcher().FireEvent( new EventEntitySpawned( gameObject ) );
}




//Destroy a game object and remove it from the game world.
void World::DestroyEntity( int objectEntityID )
{
	for ( std::vector< std::shared_ptr< GameObject > >::iterator iter = m_gameObjects.begin(); iter != m_gameObjects.end(); iter++ ) {
		if ( iter->get()->entity_id == objectEntityID ) {	
			Engine::GetInstance().GetEventDispatcher().FireEvent( new EventEntityDestroyed( *iter ) );
			m_gameObjects.erase( iter );
			return;
		}
	}
}




void World::DestroyEntity( std::shared_ptr< GameObject > entity )
{
	for ( std::vector< std::shared_ptr< GameObject > >::iterator iter = m_gameObjects.begin(); iter != m_gameObjects.end(); iter++ ) {
		if ( *iter == entity ) {
			Engine::GetInstance().GetEventDispatcher().FireEvent( new EventEntityDestroyed( *iter ) );
			m_gameObjects.erase( iter );
			return;
		}
	}
}




//Perform a raycast using the physics simulation, collect and return all hits, sorted by distance.
std::shared_ptr< RayCastResults > World::RayCast( b2Vec2 startPoint, b2Vec2 endPoint )
{
	std::shared_ptr< RayCastResults > rayCastResults( new RayCastResults() );

	physics_simulation->RayCast( rayCastResults.get(), startPoint, endPoint );

	return rayCastResults;
}




//Event listener for the post render event, to render the physics simulations' debug data.
void World::OnPostRenderEvent( std::shared_ptr< I_Event > postRenderEvent )
{
	glDisable( GL_DEPTH_TEST );
//	physics_simulation->DrawDebugData();
	glEnable( GL_DEPTH_TEST );
}




//Generate the terrain for the game world tile by tile.
void World::GenerateTerrain()
{
	for ( int x = 0; x < TILES_WIDE; x++ ) {
		for ( int y = 0; y < TILES_HIGH; y++ ) {

			//Generate a random number to determine which type of tile to place here.
			int tileSeed = rand() % 10 + 1;
			int tileType = -1;
			bool isBlocked = false;
			switch ( tileSeed ) {

			default:
				tileType = 0;
				break;
			}

			m_tileData.push_back( std::shared_ptr< TileData >( new TileData( tileType, isBlocked ) ) );
		}
	}
}




//Generate a mesh of the world's geometry for rendering.
void World::GenerateMesh()
{
	std::vector< float > worldVertices;
	std::vector< float > textureCoordinates;
	const float tilesTextureWidth = 192.0f, tilesTextureHeight = 64.0f;
	const float textureFrameSize = 32.0f;
	const float yMin = 0.0f, const yMax = TILE_SIZE;

	for ( int x = 0; x < TILES_WIDE; x++ ) {
		for ( int y = 0; y < TILES_HIGH; y++ ) {

			float xMin = x * TILE_SIZE, xMax = xMin + TILE_SIZE;
			float zMin = y * TILE_SIZE, zMax = zMin + TILE_SIZE;

			//Get the tile at this index.
			int tileType = GetTile( x, y )->tile_type;

			float yMinTexCoord = tileType * textureFrameSize / tilesTextureHeight,
				yMaxTexCoord = ( tileType * textureFrameSize + textureFrameSize ) / tilesTextureHeight;
			float xMinTexCoord = 0.0f, xMaxTexCoord = 0.0f;

			
			//BACK.
			worldVertices.push_back( xMin );	worldVertices.push_back( yMin );	worldVertices.push_back( zMax );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMin );	worldVertices.push_back( zMax );
			worldVertices.push_back( xMin );	worldVertices.push_back( yMax );	worldVertices.push_back( zMax );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMin );	worldVertices.push_back( zMax );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMax );	worldVertices.push_back( zMax );
			worldVertices.push_back( xMin );	worldVertices.push_back( yMax );	worldVertices.push_back( zMax );

			//Now calculate the UV coords normalized.
			xMinTexCoord = ( float ) 0 * textureFrameSize / tilesTextureWidth;
			xMaxTexCoord = ( float ) ( ( float ) 0 * textureFrameSize + textureFrameSize ) / tilesTextureWidth;

			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMaxTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMaxTexCoord );
			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMaxTexCoord );
			
			


			//TOP.
			worldVertices.push_back( xMin );	worldVertices.push_back( yMax );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMax );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMin );	worldVertices.push_back( yMax );	worldVertices.push_back( zMax );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMax );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMax );	worldVertices.push_back( zMax );
			worldVertices.push_back( xMin );	worldVertices.push_back( yMax );	worldVertices.push_back( zMax );

			//Now calculate the UV coords normalized.
			xMinTexCoord = ( float ) 1 * textureFrameSize / tilesTextureWidth;
			xMaxTexCoord = ( float ) ( ( float ) 1 * textureFrameSize + textureFrameSize ) / tilesTextureWidth;

			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMaxTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMaxTexCoord );
			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMaxTexCoord );

	
			


			//FRONT.
			worldVertices.push_back( xMin );	worldVertices.push_back( yMin );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMin );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMin );	worldVertices.push_back( yMax );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMin );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMax );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMin );	worldVertices.push_back( yMax );	worldVertices.push_back( zMin );

			//Now calculate the UV coords normalized.
			xMinTexCoord = ( float ) 2 * textureFrameSize / tilesTextureWidth;
			xMaxTexCoord = ( float ) ( ( float ) 2 * textureFrameSize + textureFrameSize ) / tilesTextureWidth;

			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMaxTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMaxTexCoord );
			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMaxTexCoord );
			

			


			//BOTTOM
			worldVertices.push_back( xMin );	worldVertices.push_back( yMin );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMin );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMin );	worldVertices.push_back( yMin );	worldVertices.push_back( zMax );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMin );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMin );	worldVertices.push_back( zMax );
			worldVertices.push_back( xMin );	worldVertices.push_back( yMin );	worldVertices.push_back( zMax );

			//Now calculate the UV coords normalized.
			xMinTexCoord = ( float ) 3 * textureFrameSize / tilesTextureWidth;
			xMaxTexCoord = ( float ) ( ( float ) 3 * textureFrameSize + textureFrameSize ) / tilesTextureWidth;

			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMaxTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMaxTexCoord );
			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMaxTexCoord );



			//LEFT.
			worldVertices.push_back( xMin );	worldVertices.push_back( yMin );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMin );	worldVertices.push_back( yMax );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMin );	worldVertices.push_back( yMin );	worldVertices.push_back( zMax );
			worldVertices.push_back( xMin );	worldVertices.push_back( yMax );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMin );	worldVertices.push_back( yMax );	worldVertices.push_back( zMax );
			worldVertices.push_back( xMin );	worldVertices.push_back( yMin );	worldVertices.push_back( zMax );

			//Now calculate the UV coords normalized.
			xMinTexCoord = ( float ) 4 * textureFrameSize / tilesTextureWidth;
			xMaxTexCoord = ( float ) ( ( float ) 4 * textureFrameSize + textureFrameSize ) / tilesTextureWidth;

			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMaxTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMaxTexCoord );
			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMaxTexCoord );



			//RIGHT.
			worldVertices.push_back( xMax );	worldVertices.push_back( yMin );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMax );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMin );	worldVertices.push_back( zMax );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMax );	worldVertices.push_back( zMin );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMax );	worldVertices.push_back( zMax );
			worldVertices.push_back( xMax );	worldVertices.push_back( yMin );	worldVertices.push_back( zMax );

			//Now calculate the UV coords normalized.
			xMinTexCoord = ( float ) 5 * textureFrameSize / tilesTextureWidth;
			xMaxTexCoord = ( float ) ( ( float ) 5 * textureFrameSize + textureFrameSize ) / tilesTextureWidth;

			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMaxTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMinTexCoord );
			textureCoordinates.push_back( xMaxTexCoord );				textureCoordinates.push_back( yMaxTexCoord );
			textureCoordinates.push_back( xMinTexCoord );				textureCoordinates.push_back( yMaxTexCoord );

		}
	}

	//Create a mesh for rendering.
	std::shared_ptr< Mesh > terrainMesh( new Mesh( std::shared_ptr< DefaultSpriteMaterial >( new DefaultSpriteMaterial() ) ) );
	terrainMesh->GetMaterial()->AddMaterialParameter( "activeTexture", std::shared_ptr< TextureParameter >
		( new TextureParameter( "activeTexture", ResourceManager::GetInstance().GetTexture( "Tiles" ) ) ) );
	terrainMesh->SetVertexData( worldVertices );
	terrainMesh->BindVertexAttribute( "textureCoordinates", textureCoordinates, 2 );

	std::shared_ptr< RenderComponent > terrainRenderComponent( new RenderComponent( m_worldGameObject, terrainMesh ) );
	m_worldGameObject->AddComponent( terrainRenderComponent );

}




const std::shared_ptr< TileData > World::GetTile( int xTileWorldIndex, int yTileWorldIndex )
{
	int vectorIndexPosition = yTileWorldIndex * TILES_WIDE + xTileWorldIndex;
	if ( vectorIndexPosition > m_tileData.size() ) return nullptr;
	else return m_tileData.at( vectorIndexPosition );
}