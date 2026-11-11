#include "pch.h"

#include "Animator.h"

#include "Animation.h"
#include "Object.h"

Animator::Animator()
	: m_pCurAnimation(nullptr)
	, m_pOwner(nullptr)
{

}

Animator::~Animator()
{
	Safe_Delete_Map(m_animations);
}

void Animator::Update()
{

}

void Animator::FinalUpdate()
{
	ANIMATION_TYPE animationType = GetAnimationType();
	DIR dir = m_pOwner->GetDirection();

	ChangeAnimation(animationType, dir);

	if (nullptr == m_pCurAnimation)
	{
		return;
	}

	m_pCurAnimation->Update();

	if (m_pCurAnimation->IsFinish())
	{
		STATE_ACTION actionState = m_pOwner->GetStateAction();

		if (actionState != STATE_ACTION::NONE && actionState != STATE_ACTION::DIE)
		{
			m_pOwner->SetStateAction(STATE_ACTION::NONE);
		}
	}
}

void Animator::Render(HDC dc)
{
	if (nullptr != m_pCurAnimation)
	{
		m_pCurAnimation->Render(dc);
	}
}

void Animator::CreateAnimation(ANIMATION_TYPE animationType, DIR dir, Texture* pTexture,
	Vec2 leftTop, Vec2 sliceSize, Vec2 step, float duration, UINT frameCount, bool isLoop)
{
	Animation* pAnimation = FindAnimation(animationType, dir);

	assert(nullptr == pAnimation);

	pAnimation = new Animation;

	pAnimation->SetType(animationType);
	pAnimation->m_pAnimator = this;
	pAnimation->Create(pTexture, leftTop, sliceSize, step, duration, frameCount, isLoop);

	AnimationKey animationKey = { animationType, dir };
	m_animations.insert(std::make_pair(animationKey, pAnimation));
}

Animation* Animator::FindAnimation(ANIMATION_TYPE animationType, DIR dir)
{
	AnimationKey animationKey = { animationType, dir };

	std::map<AnimationKey, Animation*>::iterator iter = m_animations.find(animationKey);

	if (iter == m_animations.end())
	{
		return nullptr;
	}

	return iter->second;
}

ANIMATION_TYPE Animator::GetAnimationType() const
{
	STATE_BASE stateBase = m_pOwner->GetStateBase();
	STATE_ACTION stateAction = m_pOwner->GetStateAction();

	switch (stateAction)
	{
	case STATE_ACTION::NONE:
		break;
	case STATE_ACTION::ATTACK:
		return ANIMATION_TYPE::ATTACK;
	case STATE_ACTION::HIT:
		return ANIMATION_TYPE::HIT;
	case STATE_ACTION::DIE:
		return ANIMATION_TYPE::DIE;
	}

	switch (stateBase)
	{
	case STATE_BASE::IDLE:
		return ANIMATION_TYPE::IDLE;
	case STATE_BASE::WALK:
		return ANIMATION_TYPE::WALK;
	case STATE_BASE::ROLL:
		return ANIMATION_TYPE::ROLL;
	case STATE_BASE::FALL:
		return ANIMATION_TYPE::FALL;
	}

	return ANIMATION_TYPE::IDLE;
}

void Animator::ChangeAnimation(ANIMATION_TYPE animationType, DIR dir)
{
	Animation* pAnimation = FindAnimation(animationType, dir);

	if (nullptr == pAnimation)
	{
		pAnimation = FindAnimation(animationType, DIR::DOWN);
	}

	if (nullptr == pAnimation || m_pCurAnimation == pAnimation)
	{
		return;
	}

	m_pCurAnimation = pAnimation;
	m_pCurAnimation->Reset();
}