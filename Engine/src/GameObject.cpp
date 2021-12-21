#include "GameObject.h"

#include "Component.h"
#include "Engine.h"

#include <glm\gtc\matrix_transform.hpp>

#include "RenderComponent.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"








GameObject::GameObject()
	: entity_id( Engine::GetInstance().GetEntityManager().CreateEntity() ),
	m_localPosition( 0.0f, 0.0f, 0.0f ), m_localRotation( 0.0f, 0.0f, 0.0f ), m_worldTransform( glm::mat4( 1.0f ) ), 
	m_parentObject( NULL ), m_parentSocketNameAttachedTo( "NULL" ), m_anchorPosition( 0.0f, 0.0f, 0.0f ), m_dimensions( 0.0f, 0.0f, 0.0f )
{
}




GameObject::~GameObject()
{
	Engine::GetInstance().GetEntityManager().DestroyEntity( entity_id );
}




void GameObject::AddComponent( std::shared_ptr< Component > component )
{
	m_components.push_back( component );
}




void GameObject::RemoveComponent( ComponentType componentType )
{
	for ( std::vector< std::shared_ptr< Component > >::iterator iter = m_components.begin(); iter != m_components.end(); iter++ ) {
		if ( iter->get()->component_type == componentType ) {
			m_components.erase( iter );
			return;
		}
	}
}




std::shared_ptr< Component > GameObject::GetComponent( ComponentType componentType )
{
	for ( std::shared_ptr< Component > component : m_components ) {
		if ( component->component_type == componentType )
			return component;
	}

	return nullptr;
}




void GameObject::BuildWorldTransform()
{
	m_worldTransform = glm::mat4( 1.0f );
	
	m_worldTransform = glm::translate( m_worldTransform, m_localPosition );


	glm::mat4 rotationMatrix = glm::mat4( 1.0f );
	rotationMatrix = glm::translate( rotationMatrix, m_anchorPosition );

	rotationMatrix = glm::rotate( rotationMatrix, m_localRotation.x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
	rotationMatrix = glm::rotate( rotationMatrix, m_localRotation.y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
	rotationMatrix = glm::rotate( rotationMatrix, m_localRotation.z, glm::vec3( 0.0f, 0.0f, 1.0f ) );
	
	rotationMatrix = glm::translate( rotationMatrix, -m_anchorPosition );


	m_worldTransform = m_worldTransform * rotationMatrix;
	if ( m_parentObject != NULL ) {
		m_worldTransform = m_parentObject->GetWorldTransform() * m_worldTransform;
	}
}




void GameObject::SetAnchorPosition( glm::vec3 anchorPosition )
{
	m_anchorPosition = anchorPosition;
}




void GameObject::AttachTo( std::shared_ptr< GameObject > parentObject, std::string optionalSocketName )
{
	m_parentObject = parentObject;

	//Check if there is a socket to attach to on the parent.
	if ( optionalSocketName != "NULL" ) {
		m_parentSocketNameAttachedTo = optionalSocketName;
		m_localPosition = m_parentObject->GetSocketLocalPosition( optionalSocketName );
		m_localRotation = m_parentObject->GetSocketLocalRotation( optionalSocketName );
	}


	parentObject->m_childObjects.push_back( shared_from_this() );
}




glm::vec3 GameObject::GetWorldPosition()
{
	glm::vec3 position = m_localPosition;
	if ( m_parentObject != NULL ) 
			position += m_parentObject->GetWorldPosition();
	return position;
}




glm::vec3 GameObject::GetSocketLocalPosition( std::string socketName )
{
	//Try finding the socket by name.
	glm::vec3 socketLocalPosition( 0.0f, 0.0f, 0.0f );

	std::shared_ptr< AnimationComponent > animationComponent = std::static_pointer_cast< AnimationComponent >( GetComponent( ComponentType::c_ANIMATION ) );
	if ( animationComponent == NULL )
		return socketLocalPosition;

	for ( std::shared_ptr< Socket > socket : animationComponent->skeletal_data.GetSockets() ) {
		if ( socket->socket_name == socketName ) {
			socketLocalPosition += socket->socket_position;
			break;
		}
	}

	return socketLocalPosition;
}




glm::vec3 GameObject::GetSocketLocalRotation( std::string socketName )
{
	//Try finding the socket by name.
	glm::vec3 socketLocalRotation( 0.0f, 0.0f, 0.0f );

	std::shared_ptr< AnimationComponent > animationComponent = std::static_pointer_cast< AnimationComponent >( GetComponent( ComponentType::c_ANIMATION ) );
	if ( animationComponent == NULL )
		return socketLocalRotation;

	for ( std::shared_ptr< Socket > socket : animationComponent->skeletal_data.GetSockets() ) {
		if ( socket->socket_name == socketName ) {
			socketLocalRotation += socket->socket_rotation;
			break;
		}
	}

	return socketLocalRotation;
}