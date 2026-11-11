#include "pch.h"

#include "EventMgr.h"

#include "SceneMgr.h"

#include "Scene.h"
#include "Object.h"

#include "UIMgr.h"

EventMgr::EventMgr()
{

}

EventMgr::~EventMgr()
{

}

void EventMgr::Update()
{
	for (size_t i = 0; i < m_deadObjects.size(); ++i)
	{
		delete m_deadObjects[i];
	}

	m_deadObjects.clear();

	for (size_t i = 0; i < m_events.size(); ++i)
	{
		Execute(m_events[i]);
	}

	m_events.clear();
}

void EventMgr::Execute(const Event& event)
{
	switch (event.eventType)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		Object* pNewObject = (Object*)event.param1;
		GROUP_TYPE type = (GROUP_TYPE)event.param2;

		SceneMgr::GetInst()->GetCurScene()->AddObject(pNewObject, type);
		break;
	}

	case EVENT_TYPE::DELETE_OBJECT:
	{
		Object* pDeadObject = (Object*)event.param1;

		if (pDeadObject->IsDead())
		{
			break;
		}

		pDeadObject->SetDead();
		m_deadObjects.push_back(pDeadObject);
		break;

	}

	case EVENT_TYPE::SCENE_CHANGE:
	{
		SceneMgr::GetInst()->ChangeScene((SCENE_TYPE)event.param1);

		UIMgr::GetInst()->SetFocusedUI(nullptr);
		break;
	}
	}
}