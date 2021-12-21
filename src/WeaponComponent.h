#pragma once








#include "Component.h"

#include <memory>

#include "FireMode.h"







//Component that is given to game objects used as weapons by other objects.
class WeaponComponent : public Component
{
	friend class FireMode;

public:


	WeaponComponent( std::shared_ptr< GameObject > parentObject )
		: Component( ComponentType::c_WEAPON, parentObject ), attack_range( 0.0f ), m_isFiring( false ), m_hasAttackBeenReleased( true )
	{  }
	

public:


	float attack_range;

	std::shared_ptr< FireMode > fire_mode;


private:


	bool m_isFiring;
	bool m_hasAttackBeenReleased;


};