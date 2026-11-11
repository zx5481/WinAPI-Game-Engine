#pragma once

#include "define.h"

class Texture;

class Core
{
	SINGLE(Core);

private:
	HWND	m_wnd;			// 메인 윈도우 핸들
	POINT	m_resolution;	// 메인 윈도우 해상도
	HDC		m_dc;			// 메인 윈도우에 Draw할 DC

	Texture* m_pBackBufferTexture;

	HBRUSH	m_brushes[(UINT)BRUSH_TYPE::END];
	HPEN	m_pens[(UINT)PEN_TYPE::END];

public:
	int Init(HWND wnd, POINT resolution);
	
	void Progress();

private:
	void CreateBrushPen();

public:
	HWND GetMainHwnd() const { return m_wnd; }
	HDC GetMainDC() const { return m_dc; }
	POINT GetResolution() const { return m_resolution; }
	HBRUSH GetBrush(BRUSH_TYPE brushType) const { return m_brushes[(UINT)brushType]; }
	HPEN GetPen(PEN_TYPE penType) const { return m_pens[(UINT)penType]; }
};