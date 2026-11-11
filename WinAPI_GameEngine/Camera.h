#pragma once

#include "pch.h"

class Object;
class Texture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct CamEffect
{
	CAM_EFFECT	effect;
	float		duration;
	float		curTime;
};

class Camera
{
	SINGLE(Camera);

private:
	Vec2					m_vecLookAt;
	Vec2					m_vecCurLookAt;
	Vec2					m_vecPrevLookAt;

	Object*					m_pTargetObject;
	Vec2					m_vecRenderOffset;

	float					m_moveTime;
	float					m_speed;
	float					m_accTime;

	std::list<CamEffect>	m_listCamEffect;
	Texture*				m_pFadeTex;

public:
	void SetLookAt(Vec2 lookAt)
	{
		m_vecLookAt = lookAt;
		float moveDist = (m_vecLookAt - m_vecPrevLookAt).Length();

		assert(m_moveTime > 0.f);

		m_speed = moveDist / m_moveTime;
		m_accTime = 0.f;
	}

	void SetTarget(Object* pTarget) { m_pTargetObject = pTarget; }
	const Vec2& GetLookAt() const { return m_vecCurLookAt; }
	Vec2 GetRenderPosition(Vec2 objectPosition) const { return objectPosition - m_vecRenderOffset; }
	Vec2 GetRealPosition(Vec2 renderPosition) const { return renderPosition + m_vecRenderOffset; }

	void FadeIn(float duration)
	{
		assert(duration > 0.f);

		CamEffect camEffect = {};
		camEffect.effect = CAM_EFFECT::FADE_IN;
		camEffect.duration = duration;
		camEffect.curTime = 0.f;

		m_listCamEffect.push_back(camEffect);
	}

	void FadeOut(float duration)
	{
		assert(duration > 0.f);

		CamEffect camEffect = {};
		camEffect.effect = CAM_EFFECT::FADE_OUT;
		camEffect.duration = duration;
		camEffect.curTime = 0.f;

		m_listCamEffect.push_back(camEffect);
	}

public:
	void Init();
	void Update();
	void Render(HDC hDC);

private:
	void CalculateRenderOffset();
};