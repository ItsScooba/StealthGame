#pragma once



#include <vector>
#include <memory>

#include "Box2D\Box2D.h"

#include "I_Event.h"

#include "GameObject.h"
#include "Mesh.h"

#include "RayCastResults.h"








//Struct used to store data about individual tile nodes within the game world.
struct TileData
{
	TileData( int tileType, bool isBlocked ) : tile_type( tileType ), is_blocked( isBlocked )
	{}

	const int tile_type;
	const bool is_blocked;
};








//Class to represent the current game world and all of the entities in it.
class World
{
public:


	World();
	~World();

	bool Initialize();
	void Shutdown();

	void Tick();

	void SpawnEntity( std::shared_ptr< GameObject > gameObject );
	void DestroyEntity( int objectEntityID );
	void DestroyEntity( std::shared_ptr< GameObject > gameObject );

	std::shared_ptr< RayCastResults > RayCast( b2Vec2 startPoint, b2Vec2 endPoint );


private:


	void GenerateTerrain();
	void GenerateMesh();

	const std::shared_ptr< TileData > GetTile( int xTileWorldIndex, int yTileWorldIndex );

	void OnPostRenderEvent( std::shared_ptr< I_Event > postRenderEvent );


public:


	const int TILES_WIDE, TILES_HIGH, TILE_SIZE;
	b2World* physics_simulation;


private:


	std::vector< std::shared_ptr< TileData > > m_tileData;
	std::shared_ptr< GameObject > m_worldGameObject;
	std::vector< std::shared_ptr< GameObject > > m_gameObjects;



};