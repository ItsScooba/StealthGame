#pragma once








#include "Component.h"

#include "AI_Controller.h"









//Component used to give an entity AI to allow it to act on it's own.
class AI_Component : public Component
{
public:


	AI_Component( std::shared_ptr< GameObject > parentObject, std::shared_ptr< AI_Controller > aiController )
		: Component( ComponentType::c_AI, parentObject ), ai_controller( aiController )
	{}


public:


	const std::shared_ptr< AI_Controller > ai_controller;

};