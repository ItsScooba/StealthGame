#pragma once








#include "Component.h"









//Component used to give a game object a health value.
class HealthComponent : public Component
{
public:


	HealthComponent( std::shared_ptr< GameObject > parentObject, int maxHealth )
		: Component( ComponentType::c_HEALTH, parentObject ), m_maxHealth( maxHealth ), m_currentHealth( maxHealth )
	{}

	~HealthComponent()
	{}


	void SetCurrentHealth( int currentHealth ) { m_currentHealth = currentHealth; }

	const int& GetCurrentHealth() { return m_currentHealth; }
	const int& GetMaxHealth() { return m_maxHealth; }


private:


	int m_maxHealth;
	int m_currentHealth;

};