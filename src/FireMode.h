#pragma once



#include <memory>

#include "GameObject.h"




//Forward Declares.
class WeaponComponent;





class FireMode
{
public:


	FireMode( std::shared_ptr< WeaponComponent > parentWeapon );
	virtual ~FireMode();

	virtual bool CanFire();

	virtual void BeginFire( const float& fireCooldownDuration );
	virtual void EndFire();
	
	virtual void Tick( const float& deltaTime );


private:


	void HandleHit( std::shared_ptr< GameObject > objectHit );

	void OnMeleeSwingEnd();


protected:


	const std::shared_ptr< WeaponComponent > m_parentWeapon;
	

private:


	float m_currentSwingTimeRemaining;
};