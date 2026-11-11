#pragma once

#include "Object.h"

class UI : public Object
{
private:
	std::vector<UI*>	m_childUIs;
	UI*					m_pParentUI;
	Vec2				m_finalPosition;

	bool m_isCamAffected;
	bool m_isMouseOn;
	bool m_isLbtnDown;

public:
	UI* GetParent() const { return m_pParentUI; }
	Vec2 GetFinalPosition() const { return m_finalPosition; }
	bool IsMouseOn() const { return m_isMouseOn; }
	bool IsLbtnDown() const { return m_isLbtnDown; }

	const std::vector<UI*>& GetChildUI() const { return m_childUIs; }

public:
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC dc);

private:
	void UpdateChild();
	void FinalUpdateChild();
	void RenderChild(HDC dc);

	void MouseOnCheck();

public:
	void AddChild(UI* pUI);

	virtual void MouseOn();

	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	virtual UI* Clone() = 0;

public:
	UI(bool isCamAffected);
	UI(const UI& origin);
	virtual ~UI();

	friend class UIMgr;
};