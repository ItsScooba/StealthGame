#include "InputAction.h"








InputAction::InputAction( std::string gameActionName, fastdelegate::FastDelegate0<> onPressedDelegate, fastdelegate::FastDelegate0<> onReleasedDelegate )
	: action_ID( gameActionName ), m_onPressedDelegate( onPressedDelegate ), m_onReleasedDelegate( onReleasedDelegate )
{

}




InputAction::~InputAction()
{

}




//Execute any delegate functions assigned to this input when it's pressed ( activated ).
void InputAction::OnPressed()
{
	if ( !m_onPressedDelegate.empty() )
		m_onPressedDelegate();
}




//Execute any delegate functions assigned to this input when it's released ( de-activated ).
void InputAction::OnReleased()
{
	if ( !m_onReleasedDelegate.empty() )
		m_onReleasedDelegate();
}