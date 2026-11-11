#include "pch.h"

#include "Object.h"
#include "Player.h"

#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"

#include "Collider.h"
#include "Animator.h"

Player::Player()
{
	CreateCollider();

	GetCollider()->SetOffsetPosition(Vec2(0.f, 12.f));

	GetCollider()->SetScale(Vec2(20.f, 40.f));

	CreateAnimator();
	Texture* pTex = ResourceMgr::GetInst()->LoadTexture(L"PlayerTexture", L"texture\\Link_Walking.bmp");
	GetAnimator()->CreateAnimation(ANIMATION_TYPE::IDLE, DIR::UP, pTex, Vec2(0.f, 260.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 1, true);
	GetAnimator()->CreateAnimation(ANIMATION_TYPE::IDLE, DIR::DOWN, pTex, Vec2(0.f, 0.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 3, true);
	GetAnimator()->CreateAnimation(ANIMATION_TYPE::IDLE, DIR::LEFT, pTex, Vec2(0.f, 130.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 1, true);
	GetAnimator()->CreateAnimation(ANIMATION_TYPE::IDLE, DIR::RIGHT, pTex, Vec2(0.f, 390.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 1, true);

	GetAnimator()->CreateAnimation(ANIMATION_TYPE::WALK, DIR::UP, pTex, Vec2(0.f, 780.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 10, true);
	GetAnimator()->CreateAnimation(ANIMATION_TYPE::WALK, DIR::DOWN, pTex, Vec2(0.f, 520.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 10, true);
	GetAnimator()->CreateAnimation(ANIMATION_TYPE::WALK, DIR::LEFT, pTex, Vec2(0.f, 650.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 10, true);
	GetAnimator()->CreateAnimation(ANIMATION_TYPE::WALK, DIR::RIGHT, pTex, Vec2(0.f, 910.f), Vec2(120.f, 130.f), Vec2(120.f, 0.f), 0.1f, 10, true);
}

Player::~Player()
{

}

void Player::Update()
{
	Vec2 position = GetPosition();
	bool isMove = false;

	if (KEY_HOLD(KEY::W))
	{
		position.y -= 300.f * fDT;
		SetDirection(DIR::UP);
		isMove = true;
	}
	if (KEY_HOLD(KEY::S))
	{
		position.y += 300.f * fDT;
		SetDirection(DIR::DOWN);
		isMove = true;
	}
	if (KEY_HOLD(KEY::A))
	{
		position.x -= 300.f * fDT;
		SetDirection(DIR::LEFT);
		isMove = true;
	}
	if (KEY_HOLD(KEY::D))
	{
		position.x += 300.f * fDT;
		SetDirection(DIR::RIGHT);
		isMove = true;
	}

	if (isMove)
	{
		SetStateBase(STATE_BASE::WALK);
	}
	else
	{
		SetStateBase(STATE_BASE::IDLE);
	}

	SetPosition(position);
}

void Player::Render(HDC dc)
{
	ComponentRender(dc);
}