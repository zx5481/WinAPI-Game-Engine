#include "pch.h"

#include "Core.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "PathMgr.h"
#include "Camera.h"
#include "SceneMgr.h"
#include "CollisionMgr.h"
#include "ResourceMgr.h"
#include "UIMgr.h"
#include "EventMgr.h"

#include "Texture.h"

Core::Core()
	: m_wnd(0)
	, m_resolution{}
	, m_dc(0)
	, m_brushes{}
	, m_pens{}
{

}

Core::~Core()
{
	ReleaseDC(m_wnd, m_dc);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_pens[i]);
	}
}

int Core::Init(HWND hWnd, POINT ptResolution)
{
	m_wnd = hWnd;
	m_resolution = ptResolution;

	RECT rt = { 0, 0, m_resolution.x, m_resolution.y };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

	SetWindowPos(m_wnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_dc = GetDC(m_wnd);

	m_pBackBufferTexture = ResourceMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_resolution.x, (UINT)m_resolution.y);

	CreateBrushPen();

	// Manager Init
	PathMgr::GetInst()->Init();
	TimeMgr::GetInst()->Init();
	KeyMgr::GetInst()->Init();
	Camera::GetInst()->Init();
	SceneMgr::GetInst()->Init();
	CollisionMgr::GetInst()->Init();

	return S_OK;
}

void Core::Progress()
{
	// Manager update

	TimeMgr::GetInst()->Update();
	KeyMgr::GetInst()->Update();
	Camera::GetInst()->Update();

	// Scene Update
	SceneMgr::GetInst()->Update();

	// Check Collision
	CollisionMgr::GetInst()->Update();

	// Check UI Event
	UIMgr::GetInst()->Update();

	// Rendering
	PatBlt(m_pBackBufferTexture->GetDC(), 0, 0, m_resolution.x, m_resolution.y, WHITENESS);

	SceneMgr::GetInst()->Render(m_pBackBufferTexture->GetDC());
	Camera::GetInst()->Render(m_pBackBufferTexture->GetDC());

	BitBlt(m_dc, 0, 0, m_resolution.x, m_resolution.y
		, m_pBackBufferTexture->GetDC(), 0, 0, SRCCOPY);


	TimeMgr::GetInst()->DebugRender();

	// Event Update (Delay)
	EventMgr::GetInst()->Update();
}

void Core::CreateBrushPen()
{
	m_brushes[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	m_pens[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_pens[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_pens[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}