#pragma once



#include <string>
#include <map>

#include "FastDelegate\FastDelegate.h"









class InputAxis
{
public:


	InputAxis( fastdelegate::FastDelegate1< float > delegateFunction );
	~InputAxis();

	void BindInputMapping( std::string inputActionName, float scaleModifier );
	bool HandleInput( const std::string& inputActionName, bool buttonStatePressed );

	void Execute();


private:


	float m_currentScalarValue;
	fastdelegate::FastDelegate1< float > m_axisDelegateFunction;
	std::map< std::string, float > m_axisMappings;


public:


	const float& GetScalar() { return m_currentScalarValue; }
};