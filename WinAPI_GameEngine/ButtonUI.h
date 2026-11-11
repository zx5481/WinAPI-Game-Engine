#pragma once

#include "UI.h"

#include "Scene.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

typedef void (Scene::* SCENE_MEMFUNC)(void);
typedef void (Object::* OBJECT_MEMFUNC) (void);

class ButtonUI : public UI
{
private:
	BTN_FUNC		m_pFunc;
	DWORD_PTR		m_param1;
	DWORD_PTR		m_param2;

	Scene*			m_pSceneInst;
	SCENE_MEMFUNC	m_pSceneFunc;

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	void SetClickedCallback(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2)
	{
		m_pFunc = pFunc;
		m_param1 = param1;
		m_param2 = param2;
	}

	void SetClickedCallback(Scene*, SCENE_MEMFUNC pSceneFunc);

	CLONE(ButtonUI);

public:
	ButtonUI();
	~ButtonUI();
};