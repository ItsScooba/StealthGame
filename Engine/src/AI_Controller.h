#pragma once



#include "Controller.h"














//Controller that handles AI and controls the entity it's using in the game world.
class AI_Controller : public Controller
{
public:


	AI_Controller();
	~AI_Controller();

	bool Initialize();
	void Unload();

	void Tick();


private:


	void UpdateActorRotation();


};