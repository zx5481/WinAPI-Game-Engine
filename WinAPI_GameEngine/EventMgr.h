#pragma once

#include "Object.h"

struct Event
{
	EVENT_TYPE eventType;
	DWORD_PTR param1;
	DWORD_PTR param2;
};

class EventMgr
{
	SINGLE(EventMgr);

private:
	std::vector<Event> m_events;
	std::vector<Object*> m_deadObjects;

public:
	void Update();

private:
	void Execute(const Event& event);

public:
	void AddEvent(const Event& event) { m_events.push_back(event); }
};