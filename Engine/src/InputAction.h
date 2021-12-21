#pragma once



#include <vector>
#include <string>

#include "FastDelegate\FastDelegate.h"







class InputAction
{
public:


	InputAction( std::string gameActionName, fastdelegate::FastDelegate0<> onPressedDelegate = fastdelegate::FastDelegate0<>(), 
		fastdelegate::FastDelegate0<> onReleasedDelegate = fastdelegate::FastDelegate0<>() );
	~InputAction();

	void OnPressed();
	void OnReleased();

public:


	const std::string action_ID;


private:


	fastdelegate::FastDelegate0<> m_onPressedDelegate;
	fastdelegate::FastDelegate0<> m_onReleasedDelegate;

};