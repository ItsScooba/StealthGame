#include "UserInterface.h"

#include "Engine.h"
#include "Renderer.h"
#include "EventDispatcher.h"












UserInterface::UserInterface()
{

}




UserInterface::~UserInterface()
{

}




bool UserInterface::Initialize()
{
	EventListener postRenderListener = fastdelegate::MakeDelegate( this, &UserInterface::OnPostRender );

	Engine::GetInstance().GetEventDispatcher().RegisterEventListener( EventType::POST_RENDER, postRenderListener );

	return true;
}




void UserInterface::Shutdown()
{
	EventListener postRenderListener = fastdelegate::MakeDelegate( this, &UserInterface::OnPostRender );

	Engine::GetInstance().GetEventDispatcher().UnregisterEventListener( EventType::POST_RENDER, postRenderListener );
}




void UserInterface::Tick()
{
	for ( std::shared_ptr< GUI_Widget > widget : m_activeWidgets ) {
		widget->Tick();
	}
}




//Callback function used for drawing the user interface on the screen, called after the rest of the scene has been drawn.
void UserInterface::OnPostRender( std::shared_ptr< I_Event > gameEvent )
{
	//Disable Z-Testing while drawing the interface, so it's drawn over anything in the scene.
	glDisable( GL_DEPTH_TEST );

	//Draw each widget on the HUD.
	for ( std::shared_ptr< GUI_Widget > widget : m_activeWidgets ) {
		widget->OnDraw();
	}

	//Re-Enable Z-Testing when finished rendering the user interface, so it's properly used throughout the scene again.
	glEnable( GL_DEPTH_TEST );
}




void UserInterface::AddWidget( std::shared_ptr< GUI_Widget > widget )
{
	m_activeWidgets.push_back( widget );
}




void UserInterface::RemoveWidget( std::string widgetID )
{
	for ( std::vector< std::shared_ptr< GUI_Widget > >::iterator widgetIter = m_activeWidgets.begin(); widgetIter != m_activeWidgets.end(); widgetIter++ ) {
		if ( widgetIter->get()->widget_ID == widgetID ) {
			m_activeWidgets.erase( widgetIter );
			return;
		}
	}
}