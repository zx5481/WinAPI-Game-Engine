#pragma once

class TimeMgr
{
	SINGLE(TimeMgr);

private:
	LARGE_INTEGER	m_curTick;
	LARGE_INTEGER	m_prevTick;
	LARGE_INTEGER	m_frequency;

	double			m_dt;
	double			m_fpsTimer;
	UINT			m_frameCount;
	UINT			m_fps;

public:
	void Init();
	void Update();
	void DebugRender();

public:
	double GetDT() const { return m_dt; }
	float GetfDT() const { return (float)m_dt; }
};