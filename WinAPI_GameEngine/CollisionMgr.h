#pragma once

class Collider;

class CollisionMgr
{
	SINGLE(CollisionMgr);

private:
	std::map<ULONGLONG, bool> m_collisionStates;
	UINT m_groupCollisionMask[static_cast<UINT>(GROUP_TYPE::END)];

public:
	void Init();
	void Update();
	void SetGroupCollision(GROUP_TYPE leftType, GROUP_TYPE rightType, bool isCheck);
	void Reset()
	{
		memset(m_groupCollisionMask, 0, sizeof(m_groupCollisionMask));
		m_collisionStates.clear();
	}

private:
	void CollisionGroupUpdate(GROUP_TYPE leftType, GROUP_TYPE rightType);
	bool IsCollision(Collider* pLeftCollider, Collider* pRightCollider);
	ULONGLONG GetColliderID(UINT leftID, UINT rightID) const;
};