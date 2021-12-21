#pragma once



#include <vector>
#include <memory>
#include <string>

#include <glm\glm.hpp>
#include "Box2D\Box2D.h"





//Forward Declares.
class Component;
enum ComponentType;









class GameObject : public std::enable_shared_from_this< GameObject >
{
public:


	GameObject();
	~GameObject();

	void AddComponent( std::shared_ptr< Component > component );
	void RemoveComponent( ComponentType componentType );
	std::shared_ptr< Component > GetComponent( ComponentType componentType );

	void SetAnchorPosition( glm::vec3 anchorPosition );
	void AttachTo( std::shared_ptr< GameObject > parentObject, std::string optionalParentSocket = "NULL" );

	glm::vec3 GetWorldPosition();
	void BuildWorldTransform();

	glm::vec3 GetSocketLocalPosition( std::string socketName );
	glm::vec3 GetSocketLocalRotation( std::string socketName );




public:


	const int entity_id;
	

private:


	std::vector< std::shared_ptr< Component > > m_components;										//Any components attached to this entity.

	std::vector< std::shared_ptr< GameObject > > m_childObjects;									//List of any child game objects attached to this game object.
	std::shared_ptr< GameObject > m_parentObject;													//The Game Object that is the parent of this game object.
	std::string m_parentSocketNameAttachedTo;														//If any, the name of the socket on the parent this entity is attached to.

	glm::vec3 m_anchorPosition;

	glm::vec3 m_localPosition;
	glm::vec3 m_localRotation;
	glm::mat4 m_worldTransform;

	glm::vec3 m_dimensions;


public:



	//======================================================================
	//Getters
	//======================================================================

	const glm::vec3& GetLocalPosition() { return m_localPosition; }
	const glm::vec3& GetLocalRotation() { return m_localRotation; }
	const glm::mat4& GetWorldTransform() { return m_worldTransform; }

	const std::vector< std::shared_ptr< GameObject > >& GetChildren() { return m_childObjects; }
	const std::shared_ptr< GameObject > GetParentObject() { return m_parentObject; }
	const std::string& GetAttachedSocketName() { return m_parentSocketNameAttachedTo; }

	const glm::vec3& GetDimensions() { return m_dimensions; }



	//======================================================================
	//Setters
	//======================================================================

	void SetLocalPosition( glm::vec3 newPosition ) {
		m_localPosition = newPosition;
	}

	void SetLocalRotation( glm::vec3 newRotation ) {
		m_localRotation = newRotation;
	}

	void SetDimensions( glm::vec3 dimensions ) {
		m_dimensions = dimensions;
	}

};