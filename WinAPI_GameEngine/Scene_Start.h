#pragma once

#include "Scene.h"

class Scene_Start : public Scene
{
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

public:
	Scene_Start();
	~Scene_Start();
};