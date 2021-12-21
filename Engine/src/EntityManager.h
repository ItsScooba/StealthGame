#pragma once



#include <vector>









class EntityManager
{
public:


	EntityManager();
	~EntityManager();

	int CreateEntity();
	void DestroyEntity( int entityID );


private:


	int m_totalAliveEntities;
	int m_nextGeneratedEntityID;
	std::vector< int > m_recycledEntityIDs;


};