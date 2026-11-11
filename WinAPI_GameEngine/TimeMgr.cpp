#include "pch.h"

#include "TimeMgr.h"
#include "Core.h"

TimeMgr::TimeMgr()
	: m_curTick{}
	, m_prevTick{}
	, m_frequency{}
	, m_dt(0.)
	, m_fpsTimer(0.)
	, m_frameCount(0)
	, m_fps(0)
{

}

TimeMgr::~TimeMgr()
{

}

void TimeMgr::Init()
{
	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_prevTick);
}

void TimeMgr::Update()
{
	QueryPerformanceCounter(&m_curTick);

	m_dt = (double)(m_curTick.QuadPart - m_prevTick.QuadPart) / (double)m_frequency.QuadPart;

	m_prevTick = m_curTick;

	// 프레임 제한
	const double maxDT = 1.0 / 60.0;
	if (m_dt > maxDT)
	{
		m_dt = maxDT;
	}
}

void TimeMgr::DebugRender()
{
	++m_frameCount;

	m_fpsTimer += m_dt;

	if (m_fpsTimer >= 1.)
	{
		m_fps = m_frameCount;

		m_fpsTimer -= 1.0;
		m_frameCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS: %d, DT: %f", m_fps, m_dt);
		SetWindowText(Core::GetInst()->GetMainHwnd(), szBuffer);
	}
}