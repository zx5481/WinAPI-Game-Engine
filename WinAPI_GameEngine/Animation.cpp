#include "pch.h"

#include "Animation.h"

#include "Camera.h"
#include "TimeMgr.h"

#include "Animator.h"
#include "Texture.h"
#include "Object.h"

Animation::Animation()
	: m_pAnimator(nullptr)
	, m_pTexture(nullptr)
	, m_curFrame(0)
	, m_elapsedTime(0.f)
	, m_isFinish(false)
	, m_isLoop(false)
{

}

Animation::~Animation()
{

}

void Animation::Update()
{
	if (m_animationFrames.empty())
	{
		return;
	}

	if (m_isFinish && m_isLoop)
	{
		return;
	}

	m_elapsedTime += fDT;

	while (m_elapsedTime >= m_animationFrames[m_curFrame].duration)
	{
		m_elapsedTime -= m_animationFrames[m_curFrame].duration;
		++m_curFrame;

		if ((int)(m_animationFrames.size()) <= m_curFrame)
		{
			if (m_isLoop)
			{
				m_curFrame = 0;
			}
			else
			{
				m_curFrame = (int)m_animationFrames.size() - 1;
				m_isFinish = true;
				m_elapsedTime = 0.f;
				return;
			}
		}
	}
}

void Animation::Render(HDC dc)
{
	if (m_animationFrames.empty())
	{
		return;
	}

	Object* pOwner = m_pAnimator->GetOwner();
	Vec2 ownerPosition = pOwner->GetPosition();

	ownerPosition += m_animationFrames[m_curFrame].offset;

	ownerPosition = Camera::GetInst()->GetRenderPosition(ownerPosition);

	TransparentBlt(dc
		, (int)(ownerPosition.x - m_animationFrames[m_curFrame].slice.x / 2.f)
		, (int)(ownerPosition.y - m_animationFrames[m_curFrame].slice.y / 2.f)
		, (int)(m_animationFrames[m_curFrame].slice.x)
		, (int)(m_animationFrames[m_curFrame].slice.y)
		, m_pTexture->GetDC()
		, (int)(m_animationFrames[m_curFrame].leftTop.x)
		, (int)(m_animationFrames[m_curFrame].leftTop.y)
		, (int)(m_animationFrames[m_curFrame].slice.x)
		, (int)(m_animationFrames[m_curFrame].slice.y)
		, RGB(255, 0, 255));
}

void Animation::Create(Texture* pTexture,
	Vec2 leftTop, Vec2 sliceSize, Vec2 step, float duration, UINT frameCount, bool isLoop)
{
	m_pTexture = pTexture;
	m_isLoop = isLoop;

	m_animationFrames.clear();

	this->Reset();

	AnimationFrame animationFrame = {};


	for (UINT i = 0; i < frameCount; ++i)
	{
		animationFrame.offset = Vec2(0.f, 0.f);
		animationFrame.duration = duration;
		animationFrame.slice = sliceSize;
		animationFrame.leftTop = leftTop + step * (float)i;

		m_animationFrames.push_back(animationFrame);
	}
}