#pragma once

#include "UI.h"

class PanelUI : public UI
{
private:
	Vec2 m_dragStart;

public:
	virtual void Update();
	virtual void Render(HDC dc);

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	CLONE(PanelUI);

public:
	PanelUI();
	~PanelUI();
};