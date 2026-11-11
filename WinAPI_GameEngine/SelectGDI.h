#pragma once

class SelectGDI
{
private:
	HDC		m_dc;
	HPEN	m_prevPen;
	HBRUSH	m_prevBrush;

public:
	SelectGDI(HDC dc, PEN_TYPE penType);
	SelectGDI(HDC dc, BRUSH_TYPE brushType);
	~SelectGDI();

	SelectGDI(const SelectGDI&) = delete;
	SelectGDI& operator=(const SelectGDI&) = delete;
};