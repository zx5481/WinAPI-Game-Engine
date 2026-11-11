#include "pch.h"

#include "SelectGDI.h"

#include "Core.h"

SelectGDI::SelectGDI(HDC hDC, PEN_TYPE penType)
	: m_dc(hDC)
	, m_prevBrush(nullptr)
	, m_prevPen(nullptr)
{
	HPEN pen = Core::GetInst()->GetPen(penType);
	m_prevPen = (HPEN)SelectObject(hDC, pen);
}

SelectGDI::SelectGDI(HDC hDC, BRUSH_TYPE brushType)
	: m_dc(hDC)
	, m_prevBrush(nullptr)
	, m_prevPen(nullptr)
{
	HBRUSH brush = Core::GetInst()->GetBrush(brushType);
	m_prevBrush = (HBRUSH)SelectObject(hDC, brush);
}

SelectGDI::~SelectGDI()
{
	if (m_prevPen)
	{
		SelectObject(m_dc, m_prevPen);
	}
	
	if (m_prevBrush)
	{
		SelectObject(m_dc, m_prevBrush);
	}
	
}