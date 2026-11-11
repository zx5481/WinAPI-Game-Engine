#pragma once

class UI;

class UIMgr
{
	SINGLE(UIMgr);
private:
	UI* m_pFocusedUI;
	UI* m_pPressedUI;

public:
	void Update();

	void SetFocusedUI(UI* pUI);

private:
	UI* GetFocusedUI();
	UI* GetTargetedUI(UI* pParentUI);
};