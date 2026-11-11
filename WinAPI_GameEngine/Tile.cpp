#include "pch.h"

#include "Object.h"

#include "Tile.h"

#include "Texture.h"

Tile::Tile()
	: m_pTileTexture(nullptr)
	, m_imageIdx(0)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

Tile::~Tile()
{

}

void Tile::Update()
{

}

void Tile::Render(HDC hDC)
{
	if (nullptr == m_pTileTexture || -1 == m_imageIdx)
	{
		return;
	}

	UINT width = m_pTileTexture->GetWidth();
	UINT height = m_pTileTexture->GetHeight();

	UINT maxCol = width / TILE_SIZE;
	UINT maxRow = height / TILE_SIZE;

	UINT curCol = (UINT)m_imageIdx % maxCol;
	UINT curRow = (UINT)m_imageIdx / maxCol;

	assert(maxRow <= curRow);

	Vec2 RenderPosition = Camera::GetInst()->GetRenderPosition(GetPosition());
	Vec2 Scale = GetScale();

	BitBlt(hDC
		, RenderPosition.x
		, RenderPosition.y
		, Scale.x
		, Scale.y
		, m_pTileTexture->GetDC()
		, curCol * TILE_SIZE
		, curRow * TILE_SIZE
		, SRCCOPY);
}

void Tile::Save(FILE* pFile)
{
	fwrite(&m_imageIdx, sizeof(int), 1, pFile);
}

void Tile::Load(FILE* pFile)
{
	fread(&m_imageIdx, sizeof(int), 1, pFile);
}