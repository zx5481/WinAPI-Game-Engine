#include "pch.h"

#include "Object.h"

#include "Collider.h"
#include "Animator.h"

Object::Object()
	: m_position{}
	, m_scale{}
	, m_dir(DIR::DOWN)
	, m_stateBase(STATE_BASE::IDLE)
	, m_stateAction(STATE_ACTION::NONE)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_isAlive(true)
{

}

Object::Object(const Object& origin)
	: m_name(origin.m_name)
	, m_position(origin.m_position)
	, m_scale(origin.m_scale)
	, m_dir(origin.m_dir)
	, m_stateBase(origin.m_stateBase)
	, m_stateAction(origin.m_stateAction)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_isAlive(true)
{
	if (nullptr != origin.m_pCollider)
	{
		m_pCollider = new Collider(*origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}

	if (nullptr != origin.m_pAnimator)
	{
		m_pAnimator = new Animator(*origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
}

Object::~Object()
{
	if (nullptr != m_pCollider)
	{
		delete m_pCollider;
	}

	if (nullptr != m_pAnimator)
	{
		delete m_pAnimator;
	}
}

void Object::CreateCollider()
{
	m_pCollider = new Collider;
	m_pCollider->m_pOwner = this;
}

void Object::CreateAnimator()
{
	m_pAnimator = new Animator;
	m_pAnimator->m_pOwner = this;
}

void Object::FinalUpdate()
{
	if (m_pCollider)
	{
		m_pCollider->FinalUpdate();
	}

	if (m_pAnimator)
	{
		m_pAnimator->FinalUpdate();
	}
}

void Object::Render(HDC hdc)
{

}

void Object::ComponentRender(HDC dc)
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->Render(dc);
	}

	if (nullptr != m_pAnimator)
	{
		m_pAnimator->Render(dc);
	}
}