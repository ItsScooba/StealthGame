#pragma once



#include <string>
#include <memory>

#include "Controller.h"

#include "Camera.h"
#include "Cursor.h"
#include "InputContext.h"
#include "UserInterface.h"








class PlayerController : public Controller
{
public:


	PlayerController();
	~PlayerController();

	bool Initialize();
	void Unload();

	void Tick();

	void ProcessInput( std::vector< InputEvent >& inputQueue );


private:


	void UpdatePlayerActorRotation();

	void MoveActorForward( float scale );
	void MoveActorRight( float scale );

	void OnAttackStart();
	void OnAttackEnd();
	void OnSprintStart();
	void OnSprintEnd();


private:



	InputContext m_inputContext;
	Camera m_camera;
	std::shared_ptr< Cursor > m_mouseCursor;
	UserInterface m_userInterface;

	float m_playerMovementSpeed;


public:
	

	Camera& GetCamera() { return m_camera; }
	std::shared_ptr< Cursor > GetCursor() { return m_mouseCursor; }
	std::shared_ptr< GameObject > GetPossessedEntity() { return m_possessedEntity; }

};