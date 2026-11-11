#include "pch.h"
#include "Collider.h"

#include "Core.h"

#include "Camera.h"

#include "Object.h"
#include "SelectGDI.h"

UINT Collider::g_nextID = 0;

Collider::Collider()
	: m_pOwner(nullptr)
	, m_offsetPosition{}
	, m_finalPosition{}
	, m_scale{}
	, m_id(g_nextID++)
	, m_collisionCount(0)
{

}

Collider::Collider(const Collider& origin)
	: m_pOwner(nullptr)
	, m_offsetPosition(origin.m_offsetPosition)
	, m_finalPosition(origin.m_finalPosition)
	, m_scale(origin.m_scale)
	, m_id(g_nextID++)
	, m_collisionCount(0)
{
	// 충돌체는 소유 관계가 명확하다.
	// 굳이 복사 생성자가 필요한가?
}

Collider::~Collider()
{

}

void Collider::FinalUpdate()
{
	assert(m_pOwner != nullptr);

	Vec2 vecObjectPosition = m_pOwner->GetPosition();
	m_finalPosition = vecObjectPosition + m_offsetPosition;

	assert(0 <= m_collisionCount);
}

void Collider::Render(HDC dc)
{
	assert(m_pOwner != nullptr);

	PEN_TYPE penType = PEN_TYPE::GREEN;

	if (m_collisionCount)
	{
		penType = PEN_TYPE::RED;
	}

	SelectGDI penSelector(dc, penType);
	SelectGDI brushSelector(dc, BRUSH_TYPE::HOLLOW);

	Vec2 renderPosition = Camera::GetInst()->GetRenderPosition(m_finalPosition);

	Rectangle(dc
		, (int)renderPosition.x - m_scale.x / 2.f
		, (int)renderPosition.y - m_scale.y / 2.f
		, (int)renderPosition.x + m_scale.x / 2.f
		, (int)renderPosition.y + m_scale.y / 2.f);
}

void Collider::OnCollision(Collider* pOther)
{
	m_pOwner->OnCollision(pOther);
}

void Collider::OnCollisionEnter(Collider* pOther)
{
	++m_collisionCount;
	m_pOwner->OnCollisionEnter(pOther);
}

void Collider::OnCollisionExit(Collider* pOther)
{
	assert(m_collisionCount > 0);
	--m_collisionCount;
	m_pOwner->OnCollisionExit(pOther);
}