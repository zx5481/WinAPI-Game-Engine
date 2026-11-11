#include "Camera.h"

#include "Core.h"
#include "Object.h"

#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ResourceMgr.h"

#include "Texture.h"

Camera::Camera()
	: m_pTargetObject(nullptr)
	, m_moveTime(0.5f)
	, m_speed(0.f)
	, m_accTime(0.5f)
	, m_pFadeTex(nullptr)
{

}

Camera::~Camera()
{

}

void Camera::Init()
{
	Vec2 vecResolution = Core::GetInst()->GetResolution();
	m_pFadeTex = ResourceMgr::GetInst()->CreateTexture(L"CameraFade", (UINT)vecResolution.x, (UINT)vecResolution.y);
}

void Camera::Update()
{
	if (m_pTargetObject)
	{
		if (m_pTargetObject->IsDead())
		{
			m_pTargetObject = nullptr;
		}
		else
		{
			m_vecLookAt = m_pTargetObject->GetPosition();
		}
	}

	if (KEY_HOLD(KEY::UP))
	{
		m_vecLookAt.y -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		m_vecLookAt.y += 500.f * fDT;
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		m_vecLookAt.x -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		m_vecLookAt.x += 500.f * fDT;
	}

	CalculateRenderOffset();
}

void Camera::Render(HDC hDC)
{
	if (m_listCamEffect.empty())
	{
		return;
	}

	float effectRatio = 0.f;

	CamEffect& camEffect = m_listCamEffect.front();

	camEffect.curTime += fDT;

	effectRatio = camEffect.curTime / camEffect.duration;

	if (effectRatio < 0.f)
	{
		effectRatio = 0.f;
	}
	if (effectRatio > 1.f)
	{
		effectRatio = 1.f;
	}

	int alpha = 0;

	if (CAM_EFFECT::FADE_OUT == camEffect.effect)
	{
		alpha = (int)(255.f * effectRatio);
	}
	else if (CAM_EFFECT::FADE_IN == camEffect.effect)
	{
		alpha = (int)(255.f * (1.f - effectRatio));
	}

	BLENDFUNCTION bf {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = alpha;

	AlphaBlend(hDC
		, 0
		, 0
		, (int)m_pFadeTex->GetWidth()
		, (int)m_pFadeTex->GetHeight()
		, m_pFadeTex->GetDC()
		, 0, 0
		, (int)m_pFadeTex->GetWidth()
		, (int)m_pFadeTex->GetHeight()
		, bf);

	if (camEffect.duration < camEffect.curTime)
	{
		m_listCamEffect.pop_front();
		return;
	}
}

void Camera::CalculateRenderOffset()
{
	m_accTime += fDT;

	if (m_moveTime <= m_accTime)
	{
		m_vecCurLookAt = m_vecLookAt;
	}
	else
	{
		Vec2 vecLookDir = m_vecLookAt - m_vecPrevLookAt;

		if (!vecLookDir.IsZero())
		{
			m_vecCurLookAt = m_vecPrevLookAt + vecLookDir.Normalize() * m_speed * fDT;
		}
	}

	Vec2 vecResolution = Core::GetInst()->GetResolution();
	Vec2 vecCenter = vecResolution / 2;

	m_vecRenderOffset = m_vecCurLookAt - vecCenter;
	m_vecPrevLookAt = m_vecCurLookAt;
}