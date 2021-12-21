#pragma once



#include "I_Event.h"









//Event fired when the application is finished rendering at the end of a frame.
class PostRenderEvent : public I_Event
{
public:


	PostRenderEvent() : I_Event( EventType::POST_RENDER ) {}
	~PostRenderEvent() {}



};