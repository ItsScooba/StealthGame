#pragma once


#include <vector>
#include <memory>

#include "GameScene.h"
#include "Window.h"
#include "Renderer.h"
#include "EntityManager.h"
#include "EventDispatcher.h"
#include "InputManager.h"
#include "I_System.h"







class Engine
{
public:


	static Engine& GetInstance()
	{
		static Engine engine;
		return engine;
	}


	~Engine();

	bool Initialize();
	void Shutdown();

	bool InitSubsystem( I_System* subSystem );
	void ShutdownSubsystem( SystemType systemType );

	void Run();

	bool SetGameScene( GameScene* gameScene );


private:


	Engine();

	void ProcessSDLEvents();


private:


	EntityManager m_entityManager;
	std::shared_ptr< GameScene > m_gameScene;
	Window m_applicationWindow;
	Renderer m_renderer;
	EventDispatcher m_eventDispatcher;
	InputManager m_inputManager;

	std::vector< std::shared_ptr< I_System > > m_activeSubsystems;


public:


	Window& GetApplicationWindow() { return m_applicationWindow; }
	Renderer& GetRenderer() { return m_renderer; }
	std::shared_ptr< GameScene > GetGameScene() { return m_gameScene; }
	EntityManager& GetEntityManager() { return m_entityManager; }
	EventDispatcher& GetEventDispatcher() { return m_eventDispatcher; }
	InputManager& GetInputManager() { return m_inputManager; }

};