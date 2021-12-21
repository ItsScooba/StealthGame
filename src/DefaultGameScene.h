#pragma once



#include "GameScene.h"







class DefaultGameScene : public GameScene
{
public:


	DefaultGameScene();
	~DefaultGameScene();

	bool Initialize();
	void Shutdown();

	void Update();




};