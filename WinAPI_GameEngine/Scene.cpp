#include "pch.h"

#include "Scene.h"

#include "Core.h"

#include "Camera.h"
#include "PathMgr.h"
#include "ResourceMgr.h"

#include "Object.h"
#include "Tile.h"


Scene::Scene()
	: m_tileX(0)
	, m_tileY(0)
{

}

Scene::~Scene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_objects[i].size(); ++j)
		{
			delete m_objects[i][j];
		}
	}
}

void Scene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_objects[i].size(); ++j)
		{
			if (!m_objects[i][j]->IsDead())
			{
				m_objects[i][j]->Update();
			}
		}
	}
}

void Scene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_objects[i].size(); ++j)
		{
			m_objects[i][j]->FinalUpdate();
		}
	}
}

void Scene::Render(HDC hDC)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		if ((UINT)GROUP_TYPE::TILE == i)
		{
			RenderTile(hDC);
			continue;
		}

		std::vector<Object*>::iterator iter = m_objects[i].begin();

		for (; iter != m_objects[i].end(); )
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(hDC);
				++iter;
			}
			else
			{
				delete *iter;
				iter = m_objects[i].erase(iter);
			}
		}
	}
}

void Scene::RenderTile(HDC hDC)
{
	const std::vector<Object*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	Vec2 camLookAt = Camera::GetInst()->GetLookAt();
	Vec2 resolution = Core::GetInst()->GetResolution();

	Vec2 leftTop = camLookAt - resolution / 2.f;

	int tileSize = TILE_SIZE;

	int leftTopCol = (int)leftTop.x / tileSize;
	int leftTopRow = (int)leftTop.y / tileSize;

	int clientWidth = ((int)resolution.x / tileSize) + 1;
	int clientHeight = ((int)resolution.y / tileSize) + 1;

	for (int curRow = leftTopRow; curRow < (leftTopRow + clientHeight); ++curRow)
	{
		for (int curCol = leftTopCol; curCol < (leftTopCol + clientWidth); ++curCol)
		{
			if (curCol < 0 || m_tileX <= curCol
				|| curRow < 0 || m_tileY <= curRow)
			{
				continue;
			}

			int index = (m_tileX * curRow) + curCol;

			vecTile[index]->Render(hDC);
		}
	}
}

void Scene::DeleteGroup(GROUP_TYPE type)
{
	Safe_Delete_Vec<Object*>(m_objects[(UINT)type]);
}

void Scene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void Scene::CreateTile(UINT countX, UINT countY)
{
	DeleteGroup(GROUP_TYPE::TILE);

	m_tileX = countX;
	m_tileY = countY;

	Texture* pTileTexture = ResourceMgr::GetInst()->LoadTexture(L"Tile", L"texture\\Tile.bmp");

	for (UINT i = 0; i < countY; ++i)
	{
		for (UINT j = 0; j < countX; ++j)
		{
			Tile* pTile = new Tile();

			pTile->SetPosition(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTexture);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void Scene::LoadTile(const std::wstring& relativePath)
{
	std::wstring filePath = PathMgr::GetInst()->GetContentPath();
	filePath += relativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, filePath.c_str(), L"rb");

	assert(pFile);

	UINT countX = 0;
	UINT countY = 0;

	fread(&countX, sizeof(UINT), 1, pFile);
	fread(&countY, sizeof(UINT), 1, pFile);

	CreateTile(countX, countY);

	const std::vector<Object*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((Tile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}