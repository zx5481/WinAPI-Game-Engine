#pragma once

class Object;

class Scene
{
private:
	std::vector<Object*>	m_objects[(UINT)GROUP_TYPE::END];
	std::wstring			m_sceneName;

	UINT					m_tileX;
	UINT					m_tileY;

public:
	void SetName(const std::wstring& name) { m_sceneName = name; }
	const std::wstring& GetName() const { return m_sceneName; }

	UINT GetTileX() const { return m_tileX; }
	UINT GetTileY() const { return m_tileY; }

	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC hDC);

	void RenderTile(HDC hDC);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	void AddObject(Object* pObject, GROUP_TYPE type) { m_objects[(UINT)type].push_back(pObject); }
	const std::vector<Object*>& GetGroupObject(GROUP_TYPE type) const { return m_objects[(UINT)type]; }

	void DeleteGroup(GROUP_TYPE type);
	void DeleteAll();

	void CreateTile(UINT countX, UINT countY);

	void LoadTile(const std::wstring& relativePath);

	std::vector<Object*>& GetUIGroup() { return m_objects[(UINT)GROUP_TYPE::UI]; }

public:
	Scene();
	virtual ~Scene();
};