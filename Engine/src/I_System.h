#pragma once



#include <vector>




#include "Component.h"
#include "I_Event.h"




//Types of systems used for identifying instances of systems.
enum SystemType
{
	s_AI,
	s_ANIMATION,
	s_PHYSICS,
	s_RENDERING,
	s_WEAPONS
};



//Base abstract class to represent a system that acts on a given set type / s of components.
class I_System
{
public:


	I_System( SystemType systemType ) 
		: system_type( systemType )
	{}
	virtual ~I_System() {};

	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;

	virtual void Update( const float& deltaTime ) = 0;							//Delta Time is the amout of time elapsed since the last update.


protected:




public:


	const SystemType system_type;


protected:


	std::vector< ComponentType > required_component_types;


};