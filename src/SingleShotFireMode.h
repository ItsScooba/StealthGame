#pragma once













#include "FireMode.h"




//Fire Mode used to shoot a single bullet with a gun / fire arm.
class SingleShotFireMode : public FireMode
{
public:


	SingleShotFireMode( std::shared_ptr< WeaponComponent > parentWeapon );
	~SingleShotFireMode();

	void BeginFire( const float& fireCooldownDuration );
	void EndFire();

	void Tick( const float& deltaTime );


private:


	void HandleHit( std::shared_ptr< GameObject > objectHit );



};