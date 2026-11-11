#include "pch.h"

#include "ButtonUI.h"

#include "Object.h"

ButtonUI::ButtonUI()
	: UI(false)
	, m_pFunc(nullptr)
	, m_param1(0)
	, m_param2(0)
	, m_pSceneInst(nullptr)
	, m_pSceneFunc(nullptr)
{

}

ButtonUI::~ButtonUI()
{

}

void ButtonUI::MouseOn()
{

}

void ButtonUI::MouseLbtnDown()
{

}

void ButtonUI::MouseLbtnUp()
{

}

void ButtonUI::MouseLbtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1, m_param2);

		m_pSceneInst = nullptr;
		m_pSceneFunc = nullptr;
	}

	if (m_pSceneInst && m_pSceneFunc)
	{
		((*m_pSceneInst).*m_pSceneFunc)();

		m_pFunc = nullptr;
		m_param1 = 0;
		m_param2 = 0;
	}
}

void ButtonUI::SetClickedCallback(Scene* pScene, SCENE_MEMFUNC pSceneFunc)
{
	m_pSceneInst = pScene;
	m_pSceneFunc = pSceneFunc;
}