#include "pch.h"

#include "PanelUI.h"

#include "KeyMgr.h"

PanelUI::PanelUI()
	: UI(false)
{

}

PanelUI::~PanelUI()
{

}

void PanelUI::Update()
{
	if (IsLbtnDown())
	{
		Vec2 diff = MOUSE_POS - m_dragStart;

		Vec2 curPosition = GetPosition();
		curPosition += diff;
		SetPosition(curPosition);

		m_dragStart = MOUSE_POS;
	}
}

void PanelUI::Render(HDC dc)
{
	UI::Render(dc);
}

void PanelUI::MouseOn()
{
	
}

void PanelUI::MouseLbtnDown()
{
	m_dragStart = MOUSE_POS;
}

void PanelUI::MouseLbtnUp()
{

}

void PanelUI::MouseLbtnClicked()
{

}