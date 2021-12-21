#include "InputAxis.h"













InputAxis::InputAxis( fastdelegate::FastDelegate1< float > delegateFunction )
	: m_axisDelegateFunction( delegateFunction ), m_currentScalarValue( 0.0f )
{
}




InputAxis::~InputAxis()
{

}




bool InputAxis::HandleInput( const std::string& inputActionID, bool buttonStatePressed )
{
	for ( std::pair< std::string, float > keyBinding : m_axisMappings ) {
		if ( keyBinding.first == inputActionID ) {
			if ( buttonStatePressed == 1 ) 
				m_currentScalarValue += keyBinding.second;
			else			   
				m_currentScalarValue -= keyBinding.second;
			
			if ( m_currentScalarValue > 1.0f ) m_currentScalarValue = 1.0f;
			if ( m_currentScalarValue < -1.0f ) m_currentScalarValue = -1.0f;

			return true;
		}
	}
	return false;
}




//Bind a button to use to change the value of the scale, which performs some kind of input.
void InputAxis::BindInputMapping( std::string inputActionID, float scaleModifier )
{
	m_axisMappings.emplace( inputActionID, scaleModifier );
}




//Execute the axis callback behavior assigned to this input axis with it's current scalar value.
void InputAxis::Execute()
{
	m_axisDelegateFunction( m_currentScalarValue );
}