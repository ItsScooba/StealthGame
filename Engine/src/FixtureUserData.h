#pragma once



#include <memory>

#include "FastDelegate\FastDelegate.h"

#include "GameObject.h"










class FixtureUserData
{
public:


	FixtureUserData( std::shared_ptr< GameObject > parentGameObject );
	~FixtureUserData();

	void SetContactBeginCallback( fastdelegate::FastDelegate1< std::shared_ptr< GameObject > > contactBeginCallback );
	void SetContactEndCallback( fastdelegate::FastDelegate1< std::shared_ptr< GameObject > > contactEndCallback );

	void OnContactBegin( std::shared_ptr< GameObject > otherObject );
	void OnContactEnd( std::shared_ptr< GameObject > otherObject );

	
public:


	const std::shared_ptr< GameObject > parent_game_object;


private:

	
	fastdelegate::FastDelegate1< std::shared_ptr< GameObject > > m_onCollisionStartCallback;
	fastdelegate::FastDelegate1< std::shared_ptr< GameObject > > m_onCollisionEndCallback;


};