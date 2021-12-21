#pragma once



#include <memory>

#include "GameObject.h"









//Interface class to represent how a controller should be implemented to control an entity with a given source.
class Controller
{
public:


	virtual bool Initialize() = 0;
	virtual void Unload() = 0;

	virtual void Tick() = 0;

	virtual void PossessEntity( std::shared_ptr< GameObject > gameObject );
	virtual void UnpossessEntity();


protected:


	std::shared_ptr< GameObject > m_possessedEntity;

};