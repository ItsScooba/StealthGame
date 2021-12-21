#include "InputContext.h"

#include "InputManager.h"











InputContext::InputContext()
{

}




InputContext::~InputContext()
{

}





void InputContext::ProcessInput( std::vector< InputEvent >& inputQueue )
{
	//Check each event in the queue, removing each event as it's processed.
	while ( !inputQueue.empty() ) {

		bool inputFound = false;
		for ( std::shared_ptr< InputAction > actionIter : m_actionMap ) {
			if ( actionIter->action_ID == inputQueue.front().input_action ) {
				
				//Found the input action tied to this action, check whether it was pressed or released.
				if ( inputQueue.front().input_state == 1 )
					actionIter->OnPressed();
				else
					actionIter->OnReleased();
				inputQueue.erase( inputQueue.begin() );
				inputFound = true;
				break;
			}
		}

		if ( !inputFound ) {
			for ( std::shared_ptr< InputAxis > axisIter : m_axisMap ) {
				if ( axisIter->HandleInput( inputQueue.begin()->input_action, inputQueue.front().input_state ) ) {
					inputQueue.erase( inputQueue.begin() );
					inputFound = true;
					break;
				}
			}
		}

		//If input is never handled, remove it from the queue anyway.
		if( !inputFound )
			inputQueue.erase( inputQueue.begin() );
	}


	//Always execute axes each frame.
	for ( auto axisIter : m_axisMap ) {
		axisIter->Execute();
	}
}




void InputContext::BindInputAction( std::shared_ptr< InputAction > inputAction )
{
	m_actionMap.push_back( inputAction );
}




void InputContext::BindInputAxis( std::shared_ptr< InputAxis > inputAxis )
{
	m_axisMap.push_back( inputAxis );
}