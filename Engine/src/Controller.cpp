#include "Controller.h"













//Possess an entity, giving this controller control over the game object.
void Controller::PossessEntity( std::shared_ptr< GameObject > gameObject )
{
	m_possessedEntity = gameObject;
}




//Unpossess any currently controlled entity.
void Controller::UnpossessEntity()
{
	m_possessedEntity = NULL;
}