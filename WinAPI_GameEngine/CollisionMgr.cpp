#include "pch.h"

#include "CollisionMgr.h"
#include "Collider.h"

#include "SceneMgr.h"

#include "Object.h"
#include "Scene.h"

CollisionMgr::CollisionMgr()
	: m_groupCollisionMask{}
{

}

CollisionMgr::~CollisionMgr()
{

}

void CollisionMgr::Init()
{

}

void CollisionMgr::Update()
{
	for (UINT row = 0; row < static_cast<UINT>(GROUP_TYPE::END); ++row)
	{
		for (UINT col = row; col < static_cast<UINT>(GROUP_TYPE::END); ++col)
		{
			if (m_groupCollisionMask[row] & (1 << col))
			{
				CollisionGroupUpdate(static_cast<GROUP_TYPE>(row), static_cast<GROUP_TYPE>(col));
			}
		}
	}
}

void CollisionMgr::CollisionGroupUpdate(GROUP_TYPE leftType, GROUP_TYPE rightType)
{
	Scene* pCurScene = SceneMgr::GetInst()->GetCurScene();

	const std::vector<Object*>& leftObjects = pCurScene->GetGroupObject(leftType);
	const std::vector<Object*>& rightObjects = pCurScene->GetGroupObject(rightType);

	std::map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < leftObjects.size(); ++i)
	{
		Object* pLeftObject = leftObjects[i];
		Collider* pLeftCollider = pLeftObject->GetCollider();

		if (nullptr == pLeftCollider)
		{
			continue;
		}

		size_t startIndex = 0;

		if (leftType == rightType)
		{
			startIndex = i + 1;
		}

		for (size_t j = startIndex; j < rightObjects.size(); ++j)
		{
			Object* pRightObject = rightObjects[j];
			Collider* pRightCollider = pRightObject->GetCollider();

			if (nullptr == pRightCollider || pLeftObject == pRightObject)
			{
				continue;
			}

			ULONGLONG colliderID = GetColliderID(pLeftCollider->GetID(), pRightCollider->GetID());

			iter = m_collisionStates.find(colliderID);

			if (m_collisionStates.end() == iter)
			{
				m_collisionStates.insert(std::make_pair(colliderID, false));
				iter = m_collisionStates.find(colliderID);
			}

			if (IsCollision(pLeftCollider, pRightCollider))
			{
				if (iter->second)
				{
					if (pLeftObject->IsDead() || pRightObject->IsDead())
					{
						pLeftCollider->OnCollisionExit(pRightCollider);
						pRightCollider->OnCollisionExit(pLeftCollider);
						iter->second = false;
					}
					else
					{
						pLeftCollider->OnCollision(pRightCollider);
						pRightCollider->OnCollision(pLeftCollider);
					}
				}
				else
				{
					if (!pLeftObject->IsDead() && !pRightObject->IsDead())
					{
						pLeftCollider->OnCollisionEnter(pRightCollider);
						pRightCollider->OnCollisionEnter(pLeftCollider);
						iter->second = true;
					}
				}
			}
			else
			{
				if (iter->second)
				{
					pLeftCollider->OnCollisionExit(pRightCollider);
					pRightCollider->OnCollisionExit(pLeftCollider);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionMgr::IsCollision(Collider* pLeftCollider, Collider* pRightCollider)
{
	Vec2 leftPosition = pLeftCollider->GetFinalPosition();
	Vec2 leftScale = pLeftCollider->GetScale();

	Vec2 rightPosition = pRightCollider->GetFinalPosition();
	Vec2 rightScale = pRightCollider->GetScale();

	if (std::abs(leftPosition.x - rightPosition.x) < (leftScale.x + rightScale.x) / 2.f
		&& std::abs(leftPosition.y - rightPosition.y) < (leftScale.y + rightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}

void CollisionMgr::SetGroupCollision(GROUP_TYPE leftType, GROUP_TYPE rightType, bool isCheck)
{
	UINT row = static_cast<UINT>(leftType);
	UINT col = static_cast<UINT>(rightType);

	if (row > col)
	{
		std::swap(row, col);
	}

	if (isCheck)
	{
		m_groupCollisionMask[row] |= (1u << col);
	}
	else
	{
		m_groupCollisionMask[row] &= ~(1u << col);
	}
}

ULONGLONG CollisionMgr::GetColliderID(UINT leftID, UINT rightID) const
{
	if (leftID > rightID)
	{
		std::swap(leftID, rightID);
	}
	return (static_cast<ULONGLONG>(leftID)) << 32 | rightID;
}