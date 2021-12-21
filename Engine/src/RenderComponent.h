#pragma once






#include <memory>

#include "Component.h"

#include "Mesh.h"
#include "Renderer.h"







class RenderComponent : public Component
{
public:


	RenderComponent( std::shared_ptr< GameObject > parentGameObject, std::shared_ptr< Mesh > meshResource, bool isDynamic = false )
		: Component( ComponentType::c_RENDERABLE, parentGameObject ), render_resource( meshResource ), is_dynamic( isDynamic )
	{  }
	~RenderComponent() {}


public:


	std::shared_ptr< Mesh > render_resource;
	const bool is_dynamic;



};