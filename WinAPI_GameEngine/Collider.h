#pragma once

class Object;

class Collider
{
private:
	static UINT g_nextID;

	Object*		m_pOwner;
	Vec2		m_offsetPosition;
	Vec2		m_finalPosition;
	Vec2		m_scale;

	UINT		m_id;

	int			m_collisionCount;

public:
	void SetOffsetPosition(Vec2 position) { m_offsetPosition = position; }
	void SetScale(Vec2 scale) { m_scale = scale; }

	Object* GetOwner() const { return m_pOwner; }
	Vec2 GetOffsetPosition() const { return m_offsetPosition; }
	Vec2 GetScale() const { return m_scale; }
	Vec2 GetFinalPosition() const { return m_finalPosition; }
	UINT GetID() const { return m_id; }

public:
	void FinalUpdate();
	void Render(HDC dc);

public:
	void OnCollision(Collider* pOther);
	void OnCollisionEnter(Collider* pOther);
	void OnCollisionExit(Collider* pOther);

	Collider& operator=(const Collider& origin) = delete;

public:
	Collider();
	Collider(const Collider& origin);
	~Collider();

	friend class Object;
};