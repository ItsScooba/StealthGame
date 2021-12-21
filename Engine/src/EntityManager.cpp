#include "EntityManager.h"













EntityManager::EntityManager() : m_totalAliveEntities( 0 ), m_nextGeneratedEntityID( 0 )
{
}




EntityManager::~EntityManager()
{

}




int EntityManager::CreateEntity()
{
	int entityID = -1;
	if ( !m_recycledEntityIDs.empty() ) {
		entityID = m_recycledEntityIDs.back();
		m_recycledEntityIDs.pop_back();
	}
	else {
		entityID = m_nextGeneratedEntityID;
		m_nextGeneratedEntityID++;
	}

	m_totalAliveEntities++;
	return entityID;
}




void EntityManager::DestroyEntity( int entityID )
{
	m_recycledEntityIDs.push_back( entityID );
	m_totalAliveEntities--;
}