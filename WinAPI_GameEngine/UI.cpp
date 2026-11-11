#include "pch.h"

#include "UI.h"
#include "Object.h"

#include "Camera.h"
#include "KeyMgr.h"

#include "SelectGDI.h"

UI::UI(bool isCamAffected)
	: m_pParentUI(nullptr)
	, m_isCamAffected(isCamAffected)
	, m_isMouseOn(false)
	, m_isLbtnDown(false)
{

}

UI::UI(const UI& origin)
	: Object(origin)
	, m_pParentUI(nullptr)
	, m_isCamAffected(origin.m_isCamAffected)
	, m_isMouseOn(false)
	, m_isLbtnDown(false)
{
	for (size_t i = 0; i < origin.m_childUIs.size(); ++i)
	{
		AddChild(origin.m_childUIs[i]->Clone());
	}
}

UI::~UI()
{
	Safe_Delete_Vec(m_childUIs);
}

void UI::Update()
{
	UpdateChild();
}

void UI::FinalUpdate()
{
	Object::FinalUpdate();

	m_finalPosition = GetPosition();

	if (GetParent())
	{
		Vec2 parentPosition = GetParent()->GetFinalPosition();
		m_finalPosition += parentPosition;
	}

	MouseOnCheck();
	FinalUpdateChild();
}

void UI::Render(HDC dc)
{
	Vec2 finalPosition = GetFinalPosition();
	Vec2 scale = GetScale();

	if (m_isCamAffected)
	{
		finalPosition = Camera::GetInst()->GetRenderPosition(finalPosition);
	}

	if (m_isLbtnDown)
	{
		SelectGDI selectGDI(dc, PEN_TYPE::GREEN);

		Rectangle(dc
			, (int)finalPosition.x
			, (int)finalPosition.y
			, (int)finalPosition.x + scale.x
			, (int)finalPosition.y + scale.y);
	}
	else
	{
		Rectangle(dc
			, (int)finalPosition.x
			, (int)finalPosition.y
			, (int)finalPosition.x + scale.x
			, (int)finalPosition.y + scale.y);
	}

	RenderChild(dc);
}

void UI::UpdateChild()
{
	for (size_t i = 0; i < m_childUIs.size(); ++i)
	{
		m_childUIs[i]->Update();
	}
}

void UI::FinalUpdateChild()
{
	for (size_t i = 0; i < m_childUIs.size(); ++i)
	{
		m_childUIs[i]->FinalUpdate();
	}
}

void UI::RenderChild(HDC dc)
{
	for (size_t i = 0; i < m_childUIs.size(); ++i)
	{
		m_childUIs[i]->Render(dc);
	}
}

void UI::AddChild(UI* pUI)

{ 
	if (nullptr == pUI)
	{
		return;
	}

	m_childUIs.push_back(pUI);
	pUI->m_pParentUI = this;
}


void UI::MouseOnCheck()
{
	Vec2 mousePosition = MOUSE_POS;
	Vec2 scale = GetScale();

	if (m_isCamAffected)
	{
		mousePosition = Camera::GetInst()->GetRealPosition(mousePosition);
	}

	if (m_finalPosition.x <= mousePosition.x && mousePosition.x <= m_finalPosition.x + scale.x
		&& m_finalPosition.y <= mousePosition.y && mousePosition.y <= m_finalPosition.y + scale.y)
	{
		m_isMouseOn = true;
	}
	else
	{
		m_isMouseOn = false;
	}
}

void UI::MouseOn()
{

}

void UI::MouseLbtnDown()
{

}

void UI::MouseLbtnUp()
{

}

void UI::MouseLbtnClicked()
{

}