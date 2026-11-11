#include "pch.h"

#include "UIMgr.h"

#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

#include "UI.h"

UIMgr::UIMgr()
	: m_pFocusedUI(nullptr)
	, m_pPressedUI(nullptr)
{

}

UIMgr::~UIMgr()
{

}

void UIMgr::Update()
{
	if (KEY_TAP(KEY::LBTN))
	{
		SetFocusedUI(GetFocusedUI());
	}

	if (!m_pFocusedUI)
	{
		return;
	}

	UI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool isLbtnTap = KEY_TAP(KEY::LBTN);
	bool isLbtnRelease = KEY_RELEASE(KEY::LBTN);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();
	}

	if (isLbtnTap)
	{
		if (nullptr != pTargetUI)
		{
			m_pPressedUI = pTargetUI;
			m_pPressedUI->m_isLbtnDown = true;
			m_pPressedUI->MouseLbtnDown();
		}
	}
	else if (isLbtnRelease)
	{
		if (nullptr != m_pPressedUI)
		{
			m_pPressedUI->MouseLbtnUp();

			if (m_pPressedUI == pTargetUI)
			{
				m_pPressedUI->MouseLbtnClicked();
			}

			m_pPressedUI->m_isLbtnDown = false;
			m_pPressedUI = nullptr;
		}
	}
}

void UIMgr::SetFocusedUI(UI* pUI)
{
	if (nullptr == pUI)
	{
		m_pFocusedUI = nullptr;
		return;
	}

	if (m_pFocusedUI == pUI)
	{
		return;
	}

	m_pFocusedUI = pUI;

	Scene* pCurScene = SceneMgr::GetInst()->GetCurScene();
	std::vector<Object*>& UIs = pCurScene->GetUIGroup();

	std::vector<Object*>::iterator iter = UIs.begin();

	for (; iter != UIs.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	if (iter != UIs.end())
	{
		UIs.erase(iter);
		UIs.push_back(m_pFocusedUI);
	}
}

UI* UIMgr::GetFocusedUI()
{
	Scene* pCurScene = SceneMgr::GetInst()->GetCurScene();
	std::vector<Object*>& UIs = pCurScene->GetUIGroup();

	std::vector<Object*>::iterator targetIter = UIs.end();

	for (std::vector<Object*>::iterator iter = UIs.begin(); iter != UIs.end(); ++iter)
	{
		if (static_cast<UI*>(*iter)->IsMouseOn())
		{
			targetIter = iter;
		}
	}

	if (UIs.end() == targetIter)
	{
		return nullptr;
	}

	return static_cast<UI*>(*targetIter);
}

UI* UIMgr::GetTargetedUI(UI* pParentUI)
{
	UI* pTargetUI = nullptr;

	std::list<UI*> queue;

	queue.push_back(pParentUI);

	while (!queue.empty())
	{
		UI* pUI = queue.front();
		queue.pop_front();

		if (pUI->IsMouseOn())
		{
			pTargetUI = pUI;
		}

		const std::vector<UI*>& childUIs = pUI->GetChildUI();
		for (size_t i = 0; i < childUIs.size(); ++i)
		{
			queue.push_back(childUIs[i]);
		}
	}

	return pTargetUI;
}