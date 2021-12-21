#pragma once



#include <memory>

#include "GameObject.h"






//Enum used to represent each component's type.
enum ComponentType
{
	//Core types.
	c_AI,
	c_ANIMATION,
	c_PHYSICS,
	c_RENDERABLE,

	c_HEALTH,
	c_WEAPON

};









//Base class for all components used to create entities into game objects.
class Component
{
public:


	Component( ComponentType componentType, std::shared_ptr< GameObject > parentGameObject )
		: component_type( componentType ), parent_entity( parentGameObject )
	{
	}

	virtual ~Component()
	{}


public:


	const ComponentType component_type;
	const std::shared_ptr< GameObject > parent_entity;


};