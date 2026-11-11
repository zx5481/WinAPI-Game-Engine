#include "pch.h"

#include "SceneMgr.h"

#include "Scene.h"

#include "Scene_Start.h"

SceneMgr::SceneMgr()
	: m_scenes{}
	, m_pCurScene(nullptr)
{

}

SceneMgr::~SceneMgr()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_scenes[i])
		{
			delete m_scenes[i];
		}
	}
}

void SceneMgr::Init()
{
	m_scenes[(UINT)SCENE_TYPE::START] = new Scene_Start;
	m_scenes[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_pCurScene = m_scenes[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void SceneMgr::Update()
{
	m_pCurScene->Update();

	m_pCurScene->FinalUpdate();
}

void SceneMgr::Render(HDC hDC)
{
	m_pCurScene->Render(hDC);
}

void SceneMgr::ChangeScene(SCENE_TYPE nextType)
{
	m_pCurScene->Exit();

	m_pCurScene = m_scenes[(UINT)nextType];

	m_pCurScene->Enter();
}