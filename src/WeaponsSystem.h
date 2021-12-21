#pragma once








#include "I_System.h"

#include <map>

#include "WeaponComponent.h"








//System for managing and updating in game weapons.
class WeaponsSystem : public I_System
{
public:


	WeaponsSystem();
	~WeaponsSystem();

	bool Initialize();
	void Shutdown();

	void Update( const float& deltaTime );


private:


	void OnEntitySpawned( std::shared_ptr< I_Event > gameEvent );
	void OnEntityDestroyed( std::shared_ptr< I_Event > gameEvent );

	void OnDamageTaken( std::shared_ptr< I_Event > gameEvent );


private:


	std::vector< std::shared_ptr< WeaponComponent > > m_weaponComponents;
	std::map< std::shared_ptr< GameObject >, float > m_activeHitMarkers;
	

};