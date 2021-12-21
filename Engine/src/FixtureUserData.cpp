#include "FixtureUserData.h"


















FixtureUserData::FixtureUserData( std::shared_ptr< GameObject > parentGameObject )
	: parent_game_object( parentGameObject ), m_onCollisionStartCallback( NULL ), m_onCollisionEndCallback( NULL )
{
	
}




FixtureUserData::~FixtureUserData()
{

}




void FixtureUserData::SetContactBeginCallback( fastdelegate::FastDelegate1< std::shared_ptr< GameObject > > contactBeginCallback )
{
	m_onCollisionStartCallback = contactBeginCallback;
}




void FixtureUserData::SetContactEndCallback( fastdelegate::FastDelegate1< std::shared_ptr< GameObject > > contactEndCallback )
{
	m_onCollisionEndCallback = contactEndCallback;
}




void FixtureUserData::OnContactBegin( std::shared_ptr< GameObject > otherObject )
{
	if( m_onCollisionStartCallback != NULL )
		m_onCollisionStartCallback( otherObject );
}




void FixtureUserData::OnContactEnd( std::shared_ptr< GameObject > otherObject )
{
	if( m_onCollisionEndCallback != NULL )
		m_onCollisionEndCallback( otherObject );
}