#pragma once

class Scene;

class SceneMgr
{
	SINGLE(SceneMgr);

private:
	Scene* m_scenes[(UINT)SCENE_TYPE::END];
	Scene* m_pCurScene;

public:
	void Init();
	void Update();
	void Render(HDC hDC);

public:
	Scene* GetCurScene() const { return m_pCurScene; }

private:
	void ChangeScene(SCENE_TYPE nextType);

	friend class EventMgr;
};