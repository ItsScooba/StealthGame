#pragma once



#include <vector>
#include <memory>

#include "GUI_Widget.h"
#include "PostRenderEvent.h"







class UserInterface
{
public:


	UserInterface();
	~UserInterface();

	bool Initialize();
	void Shutdown();

	void Tick();

	void AddWidget( std::shared_ptr< GUI_Widget > widget );
	void RemoveWidget( std::string widgetID );


private:


	void OnPostRender( std::shared_ptr< I_Event > postRenderEvent );


private:


	std::vector< std::shared_ptr< GUI_Widget > > m_activeWidgets;



};