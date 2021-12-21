#pragma once



#include <string>

#include <glm\gtc\matrix_transform.hpp>








class GUI_Widget
{
public:


	GUI_Widget( std::string widgetID );
	virtual ~GUI_Widget();

	virtual void Tick() {};
	virtual void OnDraw() {};


public:

	const std::string widget_ID;

};