#pragma once



#include <memory>
#include <vector>

#include "InputAction.h"
#include "InputAxis.h"





//Forward Declares.
struct InputEvent;




class InputContext
{
public:


	InputContext();
	~InputContext();

	void BindInputAction( std::shared_ptr< InputAction > inputAction );
	void BindInputAxis( std::shared_ptr< InputAxis > inputAxis );

	void ProcessInput( std::vector< InputEvent >& inputQueue );


private:

	std::vector< std::shared_ptr< InputAction > > m_actionMap;
	std::vector< std::shared_ptr< InputAxis > > m_axisMap;
};