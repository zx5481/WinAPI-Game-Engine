#pragma once

#include "Camera.h"

class Collider;
class Animator;

class Object
{
private:
	std::wstring	m_name;

	Vec2			m_position;
	Vec2			m_scale;

	DIR				m_dir;

	STATE_BASE		m_stateBase;
	STATE_ACTION	m_stateAction;

	Collider* m_pCollider;
	Animator* m_pAnimator;

	bool			m_isAlive;

public:
	void SetPosition(Vec2 position) { m_position = position; }
	void SetScale(Vec2 scale) { m_scale = scale; }

	const Vec2& GetPosition() const { return m_position; }
	const Vec2& GetScale() const { return m_scale; }

	void SetName(const std::wstring& name) { m_name = name; }
	const std::wstring& GetName() const { return m_name; }

	void SetDirection(DIR dir) { m_dir = dir; }
	DIR GetDirection() const { return m_dir; }

	void SetStateBase(STATE_BASE stateBase) { m_stateBase = stateBase; }
	void SetStateAction(STATE_ACTION stateAction) { m_stateAction = stateAction; }

	STATE_BASE GetStateBase() const { return m_stateBase; }
	STATE_ACTION GetStateAction() const { return m_stateAction; }

	Collider* GetCollider() { return m_pCollider; }
	Animator* GetAnimator() { return m_pAnimator; }

	Collider* GetCollider() const { return m_pCollider; }

	bool IsDead() const { return !m_isAlive; }

	void CreateCollider();
	void CreateAnimator();

	virtual void OnCollision(Collider* pOther) {}
	virtual void OnCollisionEnter(Collider* pOther) {}
	virtual void OnCollisionExit(Collider* pOther) {}

private:
	void SetDead() { m_isAlive = false; }

public:
	virtual void Update() = 0;
	virtual void FinalUpdate();
	virtual void Render(HDC hdc);

	void ComponentRender(HDC hdc);

	virtual Object* Clone() = 0;

public:
	Object();
	Object(const Object& origin);
	virtual ~Object();

	friend class EventMgr;
};