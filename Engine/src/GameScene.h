#pragma once


#include <memory>

#include "World.h"
#include "PlayerController.h"






//Main Game object. Controls starting, ending, and running the game.
class GameScene
{
public:


	GameScene();
	virtual ~GameScene();

	virtual void Quit();

	virtual bool Initialize();
	virtual void Shutdown();

	virtual void Update();


protected:


	bool m_isRunning;
	World m_gameWorld;
	std::shared_ptr< PlayerController > m_playerController;


public:


	const bool& IsRunning() { return m_isRunning; }
	World& GetWorld() { return m_gameWorld; }
	const std::shared_ptr< PlayerController > GetPlayerController() { return m_playerController; }





};
